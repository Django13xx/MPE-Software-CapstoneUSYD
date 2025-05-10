import torch
import torchvision.models as models
from torchvision import datasets, transforms
import torch.optim as optim
from torch.utils.data import DataLoader
from tqdm import tqdm  # Import tqdm for the progress bar

# Set model path
model_path = "trained_model/resnet18.pth"  # Replace with your model path

# Load model
model = models.resnet18(pretrained=False)  # Don't load pretrained weights
model.load_state_dict(torch.load(model_path, weights_only=False))  # Load model weights

# Define data transformations (ImageNet example)
transform = transforms.Compose([
    transforms.Resize(256),
    transforms.CenterCrop(224),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
])

# Load validation dataset
val_dataset = datasets.ImageFolder(root="imagenet/val", transform=transform)
val_loader = DataLoader(val_dataset, batch_size=32, shuffle=False)

# Test the model accuracy with a progress bar
def test_model(model, dataloader):
    model.eval()  # Switch to evaluation mode
    correct = 0
    total = 0
    with torch.no_grad():
        # Add tqdm here for a progress bar
        for inputs, labels in tqdm(dataloader, desc="Testing Model", unit="batch"):
            outputs = model(inputs)
            _, predicted = torch.max(outputs, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()
    
    accuracy = 100 * correct / total
    print(f"Accuracy: {accuracy:.2f}%")

# Perform accuracy testing with progress bar
test_model(model, val_loader)
