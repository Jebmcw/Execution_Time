import random
import string
import os

def random_word(length=5):
    return ''.join(random.choices(string.ascii_lowercase, k=length))

def generate_dataset(size, filename):
    dataset = []
    for _ in range(size):
        if random.choice([True, False]):
            dataset.append(random_word(random.randint(3, 8)))
        else:
            dataset.append(str(random.randint(0, 10000)))
    
    os.makedirs("data/input", exist_ok=True)
    path = f"data/input/{filename}"
    with open(path, "w") as f:
        f.write(" ".join(dataset))
    print(f"Generated {filename} with {size} elements.")

def main():
    generate_dataset(2000, "dataset_small.txt")
    generate_dataset(5000, "dataset_medium.txt")
    generate_dataset(10000, "dataset_large.txt")

if __name__ == "__main__":
    main()
