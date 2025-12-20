import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("./build/bin/data/graph.csv")
plt.plot(df["n"], df["quick_ns_per_run"], label="quick")
plt.plot(df["n"], df["ins_ns_per_run"], label="ins")
plt.legend()
plt.show()
