#!/usr/bin/env python3

import sys
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
sns.set()

def main():
    if not (2 <= len(sys.argv) and len(sys.argv) <= 3):
        print('Usage: plot.py input_file [output_file]')
        exit(1)

    input_file = sys.argv[1]
    if len(sys.argv) == 3:
        output_file = sys.argv[2]

    data = pd.read_csv(input_file)

    # sns.barplot(x='function', y='time', data=data)
    sns.lineplot(x='size', y='time', hue='function', data=data)
    plt.gca().set_xscale('log', base=2)
    plt.gca().set_yscale('log', base=10)
    plt.title('Matrix-Multiplication Benchmark')
    plt.xlabel('Matrix Size N')
    plt.ylabel('Time [s]', rotation=0, horizontalalignment='left')
    plt.gca().yaxis.set_label_coords(-0.12, 1.02)


    if len(sys.argv) == 3:
        plt.savefig(output_file)
    else:
        plt.show()


if __name__ == '__main__':
    main()
