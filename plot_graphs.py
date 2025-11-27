import pandas as pd
import matplotlib.pyplot as plt

def plot_exp3_1():
    try:
        df = pd.read_csv('exp3_1.csv')
        
        # Разделяем данные
        dense = df[df['m_type'] == 'dense']
        full = df[df['m_type'] == 'full']

        plt.figure(figsize=(10, 5))
        
        # График 1: Плотный (n^2 / 10)
        plt.subplot(1, 2, 1)
        plt.plot(dense['n'], dense['time_A'], label='Algo A (Heap)', marker='o')
        plt.plot(dense['n'], dense['time_B'], label='Algo B (Array)', marker='x')
        plt.title('m ~ n^2 / 10')
        plt.xlabel('Число вершин (n)')
        plt.ylabel('Время (с)')
        plt.legend()
        plt.grid(True)

        # График 2: Полный (n^2)
        plt.subplot(1, 2, 2)
        plt.plot(full['n'], full['time_A'], label='Algo A (Heap)', marker='o')
        plt.plot(full['n'], full['time_B'], label='Algo B (Array)', marker='x')
        plt.title('m ~ n^2 (Complete)')
        plt.xlabel('Число вершин (n)')
        plt.ylabel('Время (с)')
        plt.legend()
        plt.grid(True)

        plt.tight_layout()
        plt.savefig('result_3_1.png')
        print("Graph 3.1 saved.")
    except Exception as e:
        print(f"Skipping 3.1: {e}")

def plot_exp3_2():
    try:
        df = pd.read_csv('exp3_2.csv')
        type1 = df[df['m_type'] == '100n']
        type2 = df[df['m_type'] == '1000n']

        plt.figure(figsize=(10, 5))

        plt.subplot(1, 2, 1)
        plt.plot(type1['n'], type1['time_A'], label='Algo A (Heap)', marker='o')
        plt.plot(type1['n'], type1['time_B'], label='Algo B (Array)', marker='x')
        plt.title('m ~ 100*n (Sparse)')
        plt.xlabel('n')
        plt.ylabel('Time (s)')
        plt.legend()
        plt.grid()

        plt.subplot(1, 2, 2)
        plt.plot(type2['n'], type2['time_A'], label='Algo A (Heap)', marker='o')
        plt.plot(type2['n'], type2['time_B'], label='Algo B (Array)', marker='x')
        plt.title('m ~ 1000*n (Sparse)')
        plt.xlabel('n')
        plt.ylabel('Time (s)')
        plt.legend()
        plt.grid()

        plt.tight_layout()
        plt.savefig('result_3_2.png')
        print("Graph 3.2 saved.")
    except Exception as e:
        print(f"Skipping 3.2: {e}")

def plot_exp3_3():
    try:
        df = pd.read_csv('exp3_3.csv')
        plt.figure(figsize=(6, 4))
        plt.plot(df['m'], df['time_A'], label='Algo A (Heap)', marker='o')
        plt.plot(df['m'], df['time_B'], label='Algo B (Array)', marker='x')
        plt.title('Dependence on Edges (m) with fixed n')
        plt.xlabel('Edges (m)')
        plt.ylabel('Time (s)')
        plt.legend()
        plt.grid()
        plt.savefig('result_3_3.png')
        print("Graph 3.3 saved.")
    except:
        pass

def plot_exp3_4():
    try:
        df = pd.read_csv('exp3_4.csv')
        dense = df[df['m_type'] == 'dense']
        
        plt.figure(figsize=(6, 4))
        plt.plot(dense['r'], dense['time_A'], label='Algo A (Heap)')
        plt.plot(dense['r'], dense['time_B'], label='Algo B (Array)')
        plt.title('Dependence on Max Weight (r)')
        plt.xlabel('Max Weight (r)')
        plt.ylabel('Time (s)')
        plt.legend()
        plt.grid()
        plt.savefig('result_3_4.png')
        print("Graph 3.4 saved.")
    except:
        pass

if __name__ == "__main__":
    plot_exp3_1()
    plot_exp3_2()
    plot_exp3_3()
    plot_exp3_4()