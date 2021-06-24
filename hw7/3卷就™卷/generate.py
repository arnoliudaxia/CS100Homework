import sys
import random

try:
    from sklearn.datasets import make_blobs
except ImportError:
    print("Package scikit learn not installed, use \"python -m pip install sklearn\" for Installation")

# Specify a random seed to generate deterministic data
random.seed(123)

# Open the output file (sys.argv[2] indicates the output file name)
if len(sys.argv) != 2:
    print("Usage: python <data-file.txt>")
    exit(-1)
fi = open(sys.argv[1], "w")

# Ask for dataset parameters. Empty string triggers default values.
print("Enter dataset parameters:")
try:
    point_num = int(input("- Please input number of points (100,000 ~ 800,000) [default = 300,000]: "))
except ValueError:
    point_num = 300000
try:
    cluster_num = int(input("- Please input number of theoretical clusters (e.g., centers) (1 ~ 20) [default = 15]: "))
except ValueError:
    cluster_num = 15

box = 450   # Range of centers 
std = 25    # Standard deviation

if not (100000 <= point_num <= 800000 and 1 <= cluster_num <= 20):
    raise RuntimeError("Invalid input parameter!")

# Generate `POINT_NUM` points with `CLUSTER_NUM` Gaussian clusters.
# Here, you can set `RANDOM_STATE=CONSTANT` will generate deterministic numbers
data, clist, centers = make_blobs(n_samples=point_num, centers=cluster_num,
                         cluster_std=std, center_box=(-box, box), return_centers=True)

# Write the points data to file in a standardized format.
# The input contains `1 + center_num + point_num` lines.
# First line: <point_num> <center_num>'
# 2 ~ center_num + 1 lines: Coordinate of initial centers
# a single data point.
fi.write("%d %d\n" % (point_num, cluster_num))
for i in range(cluster_num):
    fi.write("%.8lf %.8lf\n" % (centers[i][0] + (random.random() - 0.5) * box, centers[i][1] + (random.random() - 0.5) * box))

for i in range(len(data)):
    fi.write("%.8lf %.8lf\n" % (data[i][0], data[i][1])) # All black.

# Close the data file.
fi.close()