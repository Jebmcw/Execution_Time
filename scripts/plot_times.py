import os
import pandas as pd
import matplotlib.pyplot as plt

# Get script path
base_dir = os.path.dirname(os.path.abspath(__file__))

# Load data
csv_path = os.path.normpath(os.path.join(base_dir, '..', 'data', 'output', 'times.csv'))
df = pd.read_csv(csv_path, nrows=6)
pivot_df = df.pivot(index='size', columns='algorithm', values='time_ms')

# Load hardware info
hardware_df = pd.read_csv(csv_path, skiprows=7)
cpu_raw = hardware_df.iloc[0, 0]
memory_raw = hardware_df.iloc[0, 1]
disk_raw = hardware_df.iloc[0, 2]

cpu_info = cpu_raw.split('=')[1].strip('"')
memory_bytes = int(memory_raw.split('=')[-1].strip('"'))
memory_gb = memory_bytes // (1024 ** 3)
disk_info = disk_raw.split('=')[1].strip('"')

hardware_text = f"CPU: {cpu_info}\nMemory: {memory_gb} GB\nDisk: {disk_info}"

# Plot
fig, ax = plt.subplots(figsize=(10, 6))
bar_plot = pivot_df.plot(kind='bar', ax=ax, log=True)


# Add labels above each bar
for container in bar_plot.containers:
    for bar in container:
        height = bar.get_height()
        if height > 0:
            ax.annotate(f'{height:.2f}',
                        xy=(bar.get_x() + bar.get_width() /2, height),
                        xytext=(0, 3),  # offset
                        textcoords='offset points',
                        ha='center', va='bottom',
                        fontsize=8)

# Final polish
ax.set_title('Sorting Time Comparison')
ax.set_ylabel('Time (ms, log scale)')
ax.set_xlabel('Input Size')
ax.legend(title='Algorithm')
ax.grid(True, axis='y', linestyle='--', alpha=0.7)

plt.subplots_adjust(right=0.75)
fig.text(0.77, 0.8, hardware_text, fontsize=10, va='top', ha='left',
         bbox=dict(facecolor='white', edgecolor='black'))

# Save and show
output_path = os.path.normpath(os.path.join(base_dir, '..', 'graphs', 'sorting_times.png'))
plt.tight_layout()
plt.savefig(output_path)
plt.show()
print(f"Plot saved to: {output_path}")













