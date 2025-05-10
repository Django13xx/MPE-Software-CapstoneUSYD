import subprocess
import time
import csv
import os
from pathlib import Path
import shutil
from glob import glob
import re

# Configurations
script = "resnet18_quant.py"
subset_len = 200
batch_sizes = [1, 4, 8, 16, 32, 64]
output_dir = Path("deploy_results")
xmodel_dir = Path("xmodels")
result_file = output_dir / "batchsize_results.csv"
exported_xmodel_name = "ResNet_int.xmodel"

# Ensure output directories
output_dir.mkdir(exist_ok=True)
xmodel_dir.mkdir(exist_ok=True)

# Step 1: Calibration
print(f"Step 1: Performing quantization calibration with subset_len={subset_len}...")
subprocess.run(
    f"python3 {script} --quant_mode calib --subset_len {subset_len}",
    shell=True,
    check=True
)
print("Calibration complete.")

# Step 2: Prepare results file
with open(result_file, mode="w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["batch_size", "top1_accuracy", "deploy_time_sec", "xmodel_size_kb"])

# Step 3: Test multiple batch sizes
for batch_size in batch_sizes:
    print(f"\nStep 3: Testing batch_size={batch_size}")

    # Clean up old xmodel before export
    existing = Path(exported_xmodel_name)
    if existing.exists():
        existing.unlink()
        print(f"[INFO] Removed existing {exported_xmodel_name}")

    # Step 3.1: Export quantized model
    deploy_start = time.time()
    subprocess.run(
        f"python3 {script} --quant_mode test --subset_len 1 --batch_size {batch_size} --deploy",
        shell=True,
        check=True
    )
    deploy_elapsed = round(time.time() - deploy_start, 2)

    # Step 3.2: Locate generated xmodel
    model_path = Path(exported_xmodel_name)
    if not model_path.exists():
        raise FileNotFoundError(f"[ERROR] {exported_xmodel_name} not found after deploy step.")
    
    renamed_model = xmodel_dir / f"resnet18_b{batch_size}.xmodel"
    shutil.copy(model_path, renamed_model)
    model_size_kb = round(renamed_model.stat().st_size / 1024, 2)

    print(f"[INFO] Saved model as {renamed_model.name} ({model_size_kb} KB)")

    # Step 3.3: Evaluate accuracy
    print(f"[INFO] Evaluating model accuracy (batch_size={batch_size}, subset_len=100)...")
    result = subprocess.run(
        f"python3 {script} --quant_mode test --subset_len 100 --batch_size {batch_size}",
        shell=True,
        capture_output=True,
        text=True
    )

    lines = result.stdout.splitlines()
    acc_line = next((line for line in lines if "top-1" in line.lower()), "N/A")
    acc_match = re.search(r"([0-9]+\.[0-9]+)", acc_line)
    acc_value = float(acc_match.group(1)) if acc_match else "N/A"

    # Step 3.4: Write results to CSV
    with open(result_file, mode="a", newline="") as f:
        writer = csv.writer(f)
        writer.writerow([batch_size, acc_value, deploy_elapsed, model_size_kb])

    print(f"[RESULT] Batch size {batch_size}: Accuracy={acc_value}, Export Time={deploy_elapsed}s, Size={model_size_kb}KB")

print(f"\n All experiments completed. Results saved to {result_file}")
