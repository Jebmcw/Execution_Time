# 🧪 Sorting Algorithm Performance Benchmark

This project compares the execution time of two sorting algorithms—**C++ Standard Library sort** and a manually implemented **Bubble Sort**—across datasets of varying sizes. The results are visualized with Python to evaluate performance and hardware impact.

## 📁 Project Structure

```
.
├── data/
│   ├── input/              # Auto-generated datasets
│   └── output/             # Execution time results
├── graphs/                 # Output graphs (comparison_plot.png)
├── sorting.cpp             # Main C++ benchmarking code
├── sort_runner.exe         # Compiled executable (Windows)
├── generate_dataset.py     # Python script to generate test datasets
├── plot_times.py           # Python script to visualize performance
├── build.bat               # Script to build the C++ program (Windows)
├── times.csv               # Collected execution time and hardware info
└── README.md               # This file
```

## ⚙️ How It Works

### 1. Dataset Generation

Use `generate_dataset.py` to create datasets:

```bash
python generate_dataset.py
```

This will create:

- `dataset_small.txt` (2,000 elements)  
- `dataset_medium.txt` (5,000 elements)  
- `dataset_large.txt` (10,000 elements)  

Each dataset contains a mix of random integers and lowercase words.

### 2. Execution Timing

Compile and run the C++ benchmarking program to test both:

- `std::sort` (optimized library sort)
- `bubbleSort` (naive implementation)

The program captures:

- Time taken by each algorithm
- System hardware details (CPU, RAM, Disk)

To build and run on Windows:

```bash
build.bat
sort_runner.exe
```

Execution results are saved to:

```
data/output/times.csv
```

### 3. Visualization

Use the Python plotting script to generate performance graphs:

```bash
python plot_times.py
```

This script:

- Reads `times.csv`
- Extracts and cleans hardware metadata
- Produces a bar plot with log-scaled timing results
- Saves it as: `graphs/comparison_plot.png`

## 📊 Example Output

The graph visually demonstrates:

- How execution time increases with dataset size
- The inefficiency of bubble sort at larger scales
- System hardware context for reproducibility

## 💻 System Info Integration

Hardware specs are auto-collected using WMIC commands:

- **CPU**: Name and model
- **Memory**: Total physical RAM
- **Disk**: Disk model and type

These are embedded in the plot title and/or axis annotations.

## 🧪 Dependencies

Make sure you have the following installed:

- Python 3.x
- `pandas`
- `matplotlib`
- `seaborn`

Install with:

```bash
pip install pandas matplotlib seaborn
```

## 📌 Notes

- Windows-only (due to `WMIC` usage and `sort_runner.exe`)
- Execution time results are system-dependent
- Educational purpose: Illustrates contrast between algorithmic complexity and actual performance
