import json 
import matplotlib.pyplot as plt

v_e_sum = []
avr_time = []

with open('big.txt','r') as file:
    for i in file.readlines():
        out = json.loads(i)
        v_e_sum.append(out['max_vertex'] + out['edge_amount'])
        avr_time.append(out['avr_time(ms)'] / 1000000
)
plt.rcParams.update({'font.size': 18})
fig, ax = plt.subplots()
ax.scatter(avr_time, v_e_sum)
#ax.set(title='Зависимость времени выполнения алгоритма от суммы количества рёбер и количетсва вершин')
ax.set_xlabel('Время, секунды')
ax.set_ylabel('|V| + |E|');
plt.xticks([i / 10 for i in range(0, 30)])
plt.yticks([i * 10000000 for i in range(0, 25)])
plt.grid()
plt.show()
