import subprocess
import time
import csv
import re
from pathlib import Path

# List of subset lengths to test for quantization calibration
subset_lengths = [10, 50, 100, 200, 500, 1000]

# Output CSV file to store results
result_file = "quantization_results.csv"

# Main quantization script
script = "resnet18_quant.py"

# Ensure logs directory exists
Path("logs").mkdir(exist_ok=True)

# Write CSV header
with open(result_file, mode="w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["subset_len", "top1_accuracy", "eval_time_sec"])

# Loop over all subset lengths and perform calibration + evaluation
for subset_len in subset_lengths:
    print(f"\nRunning calibration with subset_len={subset_len}")

    # Step 1: Calibration (collecting activation statistics)
    subprocess.run(
        f"python3 {script} --quant_mode calib --subset_len {subset_len}",
        shell=True,
        check=True
    )

    print("Calibration complete. Starting evaluation...")

    # Step 2: Evaluation with quantized model, measuring execution time
    start_time = time.time()
    result = subprocess.run(
        f"python3 {script} --quant_mode test",
        shell=True,
        check=True,
        capture_output=True,
        text=True
    )
    elapsed = round(time.time() - start_time, 2)

    # Step 3: Extract Top-1 accuracy from the evaluation output
    lines = result.stdout.splitlines()
    acc_line = next((line for line in lines if "Top-1" in line or "accuracy" in line.lower()), "N/A")

    # Extract numerical accuracy value using regex
    acc_match = re.search(r"([0-9]+\.[0-9]+)", acc_line)
    acc_value = float(acc_match.group(1)) if acc_match else "N/A"

    # Save full evaluation log for reference
    with open(f"logs/eval_{subset_len}.log", "w") as logf:
        logf.write(result.stdout)

    # Write results to CSV file
    with open(result_file, mode="a", newline="") as f:
        writer = csv.writer(f)
        writer.writerow([subset_len, acc_value, elapsed])

    print(f"subset_len={subset_len}: Top-1 Accuracy={acc_value}, Evaluation Time={elapsed} seconds")

print(f"\nAll experiments completed. Results saved to '{result_file}'.")