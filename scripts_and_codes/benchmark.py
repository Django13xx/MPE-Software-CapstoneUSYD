import subprocess
import csv
import time
from pathlib import Path

# Configuration
xmodel_dir = Path("xmodels")
result_file = Path("deploy_results/benchmark_results.csv")
xmodel_names = sorted(xmodel_dir.glob("resnet18_b*.xmodel"))  # e.g. resnet18_b1.xmodel, resnet18_b4.xmodel
num_images = 100  # Number of images to run per test
thread_num = 1    # Number of runner threads

# Ensure output directory exists
result_file.parent.mkdir(exist_ok=True)

# Write CSV header
with open(result_file, mode="w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["model_name", "batch_size", "FPS", "latency(ms)", "total_time_sec"])

# Loop through xmodels
for xmodel_path in xmodel_names:
    model_name = xmodel_path.name
    print(f"\n Benchmarking: {model_name}")

    # Extract batch size from filename (e.g. b1, b4, b8)
    import re
    match = re.search(r"b(\d+)", model_name)
    batch_size = int(match.group(1)) if match else "unknown"

    # Run benchmark
    start = time.time()
    result = subprocess.run(
        f"vitis_ai_benchmark -m {xmodel_path} -t {thread_num} -n {num_images}",
        shell=True,
        capture_output=True,
        text=True
    )
    elapsed = round(time.time() - start, 2)

    # Parse results
    lines = result.stdout.splitlines()
    fps = "N/A"
    latency = "N/A"
    for line in lines:
        if "FPS" in line:
            fps_match = re.search(r"FPS:\s*([0-9.]+)", line)
            if fps_match:
                fps = float(fps_match.group(1))
        if "latency" in line.lower():
            lat_match = re.search(r"latency.*:\s*([0-9.]+)", line.lower())
            if lat_match:
                latency = float(lat_match.group(1))

    # Write results
    with open(result_file, mode="a", newline="") as f:
        writer = csv.writer(f)
        writer.writerow([model_name, batch_size, fps, latency, elapsed])

    print(f"Done: batch={batch_size}, FPS={fps}, latency={latency}ms, time={elapsed}s")

print(f"\nAll benchmarking complete. Results saved to {result_file}")


# 使用前准备
# 确保你在 DPU 设备环境下运行（如 ZCU102 开发板）
# 加载环境变量：
# source /opt/vitis_ai/setup.sh

# 确保你已有多个 .xmodel，例如：
# xmodels/
#   resnet18_b1.xmodel
#   resnet18_b4.xmodel
#   resnet18_b8.xmodel

# 然后运行脚本：
# python3 run_benchmark.py



# 后续分析指标
# 你可以从表格中观察：

# 指标	含义
# FPS ↑	吞吐率是否随着 batch size 增长提升
# latency(ms) ↑	单张图片推理时间是否随 batch size 增长
# 性能平衡点	找到 batch size 最优值（高 FPS + 可控延迟）