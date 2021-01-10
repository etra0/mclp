import numpy as np
from PIL import Image
import argparse
import matplotlib.pyplot as plt
from pathlib import Path
import os

def image_to_np(file_name, max_size=500):
    image = Image.open(file_name)
    proportion = image.width / image.height
    image = image.resize((int(max_size*proportion), max_size))
    return np.asarray(image)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Generate instances from images')
    parser.add_argument('image', type=str, help='Source image to be used to generate the points (PNG or JPG only)')
    parser.add_argument('n', type=int, help='Number of points to be generated')
    parser.add_argument('--threshold', dest='threshold', default=10, type=int, help='Threshold to decide what points should be included from an averaged black and white (default 10)')
    parser.add_argument('--output-path', dest='path', default='instances/', help="The path were the files are going to end (default ./instances/)")
    args = parser.parse_args()

    if not args.image.endswith('png') and not args.image.endswith('jpg'):
        raise NotImplementedError(f"The format {args.image.split('.')[-1]} is not supported")

    if args.n <= 0:
        raise ValueError("n must be greater than 0 ")

    if args.threshold < 0:
        raise ValueError("Threshold must be greater than 0")

    data_array = image_to_np(args.image)
    black_and_white = np.flip(data_array[:, :, :3].mean(axis=2).T, 1)

    values = np.argwhere((black_and_white < args.threshold))

    assert values.size > 0, "The size of the array is 0, check your params"

    np.random.shuffle(values)
    values = values[:args.n, :]
    values *= 10000//500

    demand = (np.random.beta(0.5, 5, size=(values.shape[0], 1)) * 400).astype(int)
    demand[demand == 0] = 1

    with_dimension = np.hstack((values, demand))

    file_basename = Path(args.image).resolve().name
    file_basename = file_basename.strip(".png").strip(".jpg")

    with open(os.path.join(args.path, f"{file_basename}.txt"), "w") as f:
        f.write(f"{with_dimension.shape[0]}\n")
        for (x, y) in with_dimension[:, :2]:
            f.write(f"{x} {y}\n")

    with open(os.path.join(args.path, f"demand-{file_basename}.dat"), "w") as f:
        for x in with_dimension[:, 2]:
            f.write(f"{x}\n")
