# From Software to Silicon: ResNet-18 Quantization and FPGA Deployment

## Project Overview
This repository presents a reproducible end-to-end framework to assist **software engineers** in deploying **ResNet-18** deep learning models onto **FPGA hardware** using **Vitis AI**.  
The project demonstrates the complete workflow from **PyTorch model quantization** to **FPGA execution**, providing a practical methodology for bridging the gap between software and hardware engineering.

The work was completed as part of the **ELEC5021 Capstone Project B** at **The University of Sydney**, aiming to lower the barrier for software engineers to enter the FPGA acceleration domain.

## Repository Structure and Features

### 1. `1_quantize_results/`
Contains model artifacts generated from **quantization experiments** with different `batch_size` settings:
- `ResNet_int.xmodel`: Quantized Xilinx model for deployment.
- `ResNet_int.onnx`: ONNX version of the quantized model.
- `ResNet_int_Structure.onnx.png`: Visualization of the model architecture using [netron.app](https://netron.app/).
- `ResNet.py`: The quantizable module script.
- `ResNet_int.pt`, `bias_corr.pth`: Quantized model weights and calibration data.

### 2. `2_compiler_result/`
Includes:
- `resnet_c.xmodel`: FPGA DPU-compiled model ready for ZCU102 board deployment.
- Additional logs and intermediate files generated during the **Vitis AI Compiler (`vai_c_xir`)** process.

### 3. `3_vitisHLS_simulation_results/`
#### 3.1 `resblock_hls/src/`
- `resblock.cpp`, `resblock_tb.cpp`: C++ source and testbench files used for **HLS (High-Level Synthesis)** simulation of ResNet blocks.

#### 3.2 Simulation Backups:
- `resnet_hls_xcvu9p-flga2104-2-e_backup/`
- `resnet_hls_zcu102_backup/`
  > These contain Vitis HLS workspace backups for **UltraScale+** and **ZCU102** platforms, supporting performance analysis replication.

### 4. `scripts_and_codes/`
Contains **all automation scripts** supporting the project workflow:

| Script | Description |
|-------|-------------|
| **`test_resnet18_original.py`** | Tests pre-quantization ResNet-18 model accuracy. |
| **`resnet18_quant.py`** | Main quantization script adapted from [Xilinx Official Example](https://github.com/Xilinx/Vitis-AI/blob/master/src/vai_quantizer/vai_q_pytorch/README.md). Supports calibration, testing, and export. |
| **`benchmark`** | Example wrapper for model compilation using `vai_c_xir`. |
| **`quant_experiment.py`** | Automates experiments on different `subset_len` values for quantization calibration. |
| **`batch_experiment.py`** | Automates experiments on different `batch_size` values during export to evaluate structural consistency. |

### 5. `trained_model/`
- `resnet18.pth`: Official [pre-trained ResNet-18](https://github.com/Xilinx/Vitis-AI/blob/master/src/vai_quantizer/vai_q_pytorch/README.md) model weights, serving as the starting point for quantization.

---

## Environment & Software Requirements

| Component                    | Version             | Notes |
|------------------------------|---------------------|------|
| **Host OS**                   | Windows 10/11 / MacOS 10+ | Recommended for VM setup |
| **VM Platform**               | VMware Workstation Pro | [Free Download](https://blogs.vmware.com/workstation/2024/05/vmware-workstation-pro-now-available-free-for-personal-use.html) |
| **VM OS**                     | Ubuntu 20.04.6 LTS or 22.04.6 LTS | [Download Ubuntu](https://releases.ubuntu.com/focal/) |
| **Docker**                    | 28.0.4 or higher    | [Install Docker](https://docs.docker.com/desktop/setup/install/linux/ubuntu/) |
| **Vitis AI**                  | 3.5.0               | [Official Installation Guide](https://xilinx.github.io/Vitis-AI/3.5/html/index.html) |
| **GCC (in Vitis AI)**         | 7.5.0               | Pre-installed in Vitis AI environment |
| **Python (in Vitis AI)**      | 3.8.6               | Pre-installed in Vitis AI environment |
| **PyTorch (in Vitis AI)**     | 1.13.1              | Pre-installed in Vitis AI environment |
| **torchvision (in Vitis AI)** | 0.14                | Pre-installed in Vitis AI environment |
| **vai_q_pytorch**             | 3.5.0+60df3f1+torch1.13.1 | Pre-installed in Vitis AI environment |
| **Vitis HLS**                 | Latest version      | Supports UltraScale+ and ZCU102 target platforms |

---

## System Workflow

1. **Environment Setup**  
   - Install VMware, Ubuntu, Docker, and Vitis AI runtime.

2. **Model Preparation**  
   - Load and validate `resnet18.pth` pre-trained model.

3. **Model Quantization**  
   - Run `resnet18_quant.py` for calibration and testing.
   - Conduct subset length (`subset_len`) and batch size (`batch_size`) experiments.

4. **Model Compilation**  
   - Use `vai_c_xir` to compile `.xmodel` targeting ZCU102 DPU.

5. **HLS Simulation**  
   - Run Vitis HLS on ResNet residual block (`resblock.cpp`) for resource and latency analysis.

6. **Results Verification**  
   - Validate model accuracy and performance on target hardware or simulation tools.

---

## Usage Guide

### 1. Pull Vitis AI Docker Environment
```bash
docker pull xilinx/vitis-ai-pytorch-cpu:latest
docker run -it xilinx/vitis-ai-pytorch-cpu:latest /bin/bash
```

### 2. Run Quantization Example
```bash
python resnet18_quant.py --quant_mode calib --subset_len 200
python resnet18_quant.py --quant_mode test
python resnet18_quant.py --quant_mode test --subset_len 1 --batch_size 1 --deploy
```

### 3. Compile for FPGA Deployment
```bash
vai_c_xir -x quantize_result/ResNet_int.xmodel \
         -a /opt/vitis_ai/compiler/arch/DPUCZDX8G/ZCU102/arch.json \
         -o compiler_result \
         -n resnet_c
```
## Team Information

### Student Name: Renjie Yao

### SID: `520203600`

### Supervisor: Professor David Boland

## Live Demo
Coming soon...

## License
MIT License
Free to use, copy, modify, and distribute for academic and non-commercial purposes.
See LICENSE file for more details.
