import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def plot_exp3_1():
    try:
        df = pd.read_csv('exp3_1.csv')
        
        # Разделяем данные - теперь другие названия
        case_a = df[df['m_type'] == 'n2_div_10']
        case_b = df[df['m_type'] == 'n2']

        plt.figure(figsize=(12, 5))
        
        # График 1: m ≈ n²/10
        plt.subplot(1, 2, 1)
        plt.plot(case_a['n'], case_a['time_A'], label='Алгоритм A (15-куча)', marker='o', markersize=3)
        plt.plot(case_a['n'], case_a['time_B'], label='Алгоритм B (массивы)', marker='x', markersize=3)
        plt.title('m ≈ n²/10')
        plt.xlabel('Число вершин (n)')
        plt.ylabel('Время (с)')
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.yscale('log')  # Логарифмическая шкала для времени

        # График 2: m ≈ n²
        plt.subplot(1, 2, 2)
        plt.plot(case_b['n'], case_b['time_A'], label='Алгоритм A (15-куча)', marker='o', markersize=3)
        plt.plot(case_b['n'], case_b['time_B'], label='Алгоритм B (массивы)', marker='x', markersize=3)
        plt.title('m ≈ n²')
        plt.xlabel('Число вершин (n)')
        plt.ylabel('Время (с)')
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.yscale('log')  # Логарифмическая шкала для времени

        plt.suptitle('Эксперимент 3.1: Зависимость времени от n при разных плотностях графа', fontsize=14)
        plt.tight_layout()
        plt.savefig('result_3_1.png', dpi=300)
        plt.savefig('result_3_1.pdf')
        print("График 3.1 сохранен (result_3_1.png)")
        
        # Также сохраняем данные в отдельные файлы для детального анализа
        case_a.to_csv('exp3_1_case_a.csv', index=False)
        case_b.to_csv('exp3_1_case_b.csv', index=False)
        
    except Exception as e:
        print(f"Ошибка при построении графика 3.1: {e}")

def plot_exp3_2():
    try:
        df = pd.read_csv('exp3_2.csv')
        case_a = df[df['m_type'] == '100n']
        case_b = df[df['m_type'] == '1000n']

        plt.figure(figsize=(12, 5))

        # График 1: m ≈ 100·n
        plt.subplot(1, 2, 1)
        plt.plot(case_a['n'], case_a['time_A'], label='Алгоритм A (15-куча)', marker='o', markersize=3)
        plt.plot(case_a['n'], case_a['time_B'], label='Алгоритм B (массивы)', marker='x', markersize=3)
        plt.title('m ≈ 100·n')
        plt.xlabel('Число вершин (n)')
        plt.ylabel('Время (с)')
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.yscale('log')

        # График 2: m ≈ 1000·n
        plt.subplot(1, 2, 2)
        plt.plot(case_b['n'], case_b['time_A'], label='Алгоритм A (15-куча)', marker='o', markersize=3)
        plt.plot(case_b['n'], case_b['time_B'], label='Алгоритм B (массивы)', marker='x', markersize=3)
        plt.title('m ≈ 1000·n')
        plt.xlabel('Число вершин (n)')
        plt.ylabel('Время (с)')
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.yscale('log')

        plt.suptitle('Эксперимент 3.2: Зависимость времени от n при m ∝ n', fontsize=14)
        plt.tight_layout()
        plt.savefig('result_3_2.png', dpi=300)
        plt.savefig('result_3_2.pdf')
        print("График 3.2 сохранен (result_3_2.png)")
        
        # Сохраняем данные для анализа
        case_a.to_csv('exp3_2_case_a.csv', index=False)
        case_b.to_csv('exp3_2_case_b.csv', index=False)
        
    except Exception as e:
        print(f"Ошибка при построении графика 3.2: {e}")

def plot_exp3_3():
    try:
        df = pd.read_csv('exp3_3.csv')
        plt.figure(figsize=(8, 5))
        
        plt.plot(df['m'], df['time_A'], label='Алгоритм A (15-куча)', marker='o', linewidth=2)
        plt.plot(df['m'], df['time_B'], label='Алгоритм B (массивы)', marker='s', linewidth=2)
        
        plt.title('Эксперимент 3.3: Зависимость времени от количества рёбер (m)\nn = 10001 (фиксировано)', fontsize=14)
        plt.xlabel('Количество рёбер (m)')
        plt.ylabel('Время (с)')
        plt.legend()
        plt.grid(True, alpha=0.3)
        
        # Добавляем аннотации для некоторых точек
        for i in range(0, len(df), 2):
            plt.annotate(f"{df['time_A'].iloc[i]:.3f}s", 
                        (df['m'].iloc[i], df['time_A'].iloc[i]),
                        textcoords="offset points", xytext=(0,10), ha='center', fontsize=8)
            plt.annotate(f"{df['time_B'].iloc[i]:.3f}s", 
                        (df['m'].iloc[i], df['time_B'].iloc[i]),
                        textcoords="offset points", xytext=(0,-15), ha='center', fontsize=8)
        
        plt.tight_layout()
        plt.savefig('result_3_3.png', dpi=300)
        plt.savefig('result_3_3.pdf')
        print("График 3.3 сохранен (result_3_3.png)")
        
        # Сохраняем данные для анализа
        df.to_csv('exp3_3_detailed.csv', index=False)
        
    except Exception as e:
        print(f"Ошибка при построении графика 3.3: {e}")

def plot_exp3_4():
    try:
        df = pd.read_csv('exp3_4.csv')
        dense = df[df['m_type'] == 'dense']
        sparse = df[df['m_type'] == 'sparse']
        
        plt.figure(figsize=(12, 5))
        
        # График 1: Плотный граф (m ≈ n²)
        plt.subplot(1, 2, 1)
        plt.plot(dense['r'], dense['time_A'], label='Алгоритм A (15-куча)', marker='o', markersize=3)
        plt.plot(dense['r'], dense['time_B'], label='Алгоритм B (массивы)', marker='x', markersize=3)
        plt.title('Плотный граф (m ≈ n²)')
        plt.xlabel('Максимальный вес рёбер (r)')
        plt.ylabel('Время (с)')
        plt.legend()
        plt.grid(True, alpha=0.3)
        
        # График 2: Разреженный граф (m ≈ 1000·n)
        plt.subplot(1, 2, 2)
        plt.plot(sparse['r'], sparse['time_A'], label='Алгоритм A (15-куча)', marker='o', markersize=3)
        plt.plot(sparse['r'], sparse['time_B'], label='Алгоритм B (массивы)', marker='x', markersize=3)
        plt.title('Разреженный граф (m ≈ 1000·n)')
        plt.xlabel('Максимальный вес рёбер (r)')
        plt.ylabel('Время (с)')
        plt.legend()
        plt.grid(True, alpha=0.3)
        
        plt.suptitle('Эксперимент 3.4: Зависимость времени от диапазона весов рёбер (r)\nn = 10001 (фиксировано)', fontsize=14)
        plt.tight_layout()
        plt.savefig('result_3_4.png', dpi=300)
        plt.savefig('result_3_4.pdf')
        print("График 3.4 сохранен (result_3_4.png)")
        
        # Сохраняем данные для анализа
        dense.to_csv('exp3_4_dense.csv', index=False)
        sparse.to_csv('exp3_4_sparse.csv', index=False)
        
    except Exception as e:
        print(f"Ошибка при построении графика 3.4: {e}")

def plot_comparison_all():
    """Сводный график для сравнения всех экспериментов"""
    try:
        fig, axes = plt.subplots(2, 2, figsize=(14, 10))
        
        # Эксперимент 3.1 (случай m ≈ n²/10)
        df1 = pd.read_csv('exp3_1.csv')
        case1 = df1[df1['m_type'] == 'n2_div_10']
        axes[0, 0].plot(case1['n'], case1['time_A'], 'b-', label='A (15-куча)', linewidth=1.5)
        axes[0, 0].plot(case1['n'], case1['time_B'], 'r-', label='B (массивы)', linewidth=1.5)
        axes[0, 0].set_title('3.1: m ≈ n²/10')
        axes[0, 0].set_xlabel('n')
        axes[0, 0].set_ylabel('Время (с)')
        axes[0, 0].legend()
        axes[0, 0].grid(True, alpha=0.3)
        axes[0, 0].set_yscale('log')
        
        # Эксперимент 3.2 (случай m ≈ 1000·n)
        df2 = pd.read_csv('exp3_2.csv')
        case2 = df2[df2['m_type'] == '1000n']
        axes[0, 1].plot(case2['n'], case2['time_A'], 'b-', label='A (15-куча)', linewidth=1.5)
        axes[0, 1].plot(case2['n'], case2['time_B'], 'r-', label='B (массивы)', linewidth=1.5)
        axes[0, 1].set_title('3.2: m ≈ 1000·n')
        axes[0, 1].set_xlabel('n')
        axes[0, 1].set_ylabel('Время (с)')
        axes[0, 1].legend()
        axes[0, 1].grid(True, alpha=0.3)
        axes[0, 1].set_yscale('log')
        
        # Эксперимент 3.3
        df3 = pd.read_csv('exp3_3.csv')
        axes[1, 0].plot(df3['m'], df3['time_A'], 'b-', label='A (15-куча)', linewidth=1.5)
        axes[1, 0].plot(df3['m'], df3['time_B'], 'r-', label='B (массивы)', linewidth=1.5)
        axes[1, 0].set_title('3.3: Зависимость от m (n=10001)')
        axes[1, 0].set_xlabel('m')
        axes[1, 0].set_ylabel('Время (с)')
        axes[1, 0].legend()
        axes[1, 0].grid(True, alpha=0.3)
        
        # Эксперимент 3.4 (плотный граф)
        df4 = pd.read_csv('exp3_4.csv')
        case4 = df4[df4['m_type'] == 'dense']
        axes[1, 1].plot(case4['r'], case4['time_A'], 'b-', label='A (15-куча)', linewidth=1.5)
        axes[1, 1].plot(case4['r'], case4['time_B'], 'r-', label='B (массивы)', linewidth=1.5)
        axes[1, 1].set_title('3.4: Зависимость от r (плотный граф)')
        axes[1, 1].set_xlabel('r')
        axes[1, 1].set_ylabel('Время (с)')
        axes[1, 1].legend()
        axes[1, 1].grid(True, alpha=0.3)
        
        plt.suptitle('Сводное сравнение всех экспериментов', fontsize=16)
        plt.tight_layout()
        plt.savefig('result_all_comparison.png', dpi=300)
        plt.savefig('result_all_comparison.pdf')
        print("Сводный график сохранен (result_all_comparison.png)")
        
    except Exception as e:
        print(f"Ошибка при построении сводного графика: {e}")

if __name__ == "__main__":
    print("=" * 60)
    print("ВИЗУАЛИЗАЦИЯ РЕЗУЛЬТАТОВ ЭКСПЕРИМЕНТОВ")
    print("=" * 60)
    
    plot_exp3_1()
    plot_exp3_2()
    plot_exp3_3()
    plot_exp3_4()
    plot_comparison_all()
    
    print("\n" + "=" * 60)
    print("ВСЕ ГРАФИКИ СОХРАНЕНЫ:")
    print("1. result_3_1.png/pdf - Эксперимент 3.1")
    print("2. result_3_2.png/pdf - Эксперимент 3.2")
    print("3. result_3_3.png/pdf - Эксперимент 3.3")
    print("4. result_3_4.png/pdf - Эксперимент 3.4")
    print("5. result_all_comparison.png/pdf - Сводное сравнение")
    print("=" * 60)