#include <iostream>
#include <cstdint>
#include <stack>
#include <vector>
#include <ctime>
#include "head.h"

//определяет порядковый номер рассматриваемой вершины 
uint32_t idx = 0;
//стек, куда кладутся персональные индексы вершин
std::stack<uint32_t> component;

struct Vertex
{
    //персональный индекс вершины
    uint32_t personal_idx = 0;
    //порядковый номер вершины
    uint32_t global_idx = 0;
    //минимальный порядковый номер вершины в той же компоненте свзяности
    uint32_t lowlink = 0;
    //есть ли вершина на стеке
    bool on_stack = 0;
    //заходили ли мы когда-нибудь в эту вершину
    bool used = 0;
};

void strongconnect(Vertex& v, Vertex* V, std::vector<uint32_t>* E)
{
    //присваиваем порядковые номера
    v.global_idx = idx;
    v.lowlink = idx;
    //увеличиваем глобальный счётчик
    ++idx;
    //кладём вершину на стек
    component.push(v.personal_idx);
    //актуализируем информацию
    v.on_stack = 1;
    v.used = 1;

    //начинаем рассматривать все вершины, в которые мы можем прийти
    for(uint32_t i = 0; i < E[v.personal_idx].size(); ++i)
    {
        //вершина, в которую мы собираемся перейти
        Vertex* w = &V[E[v.personal_idx][i]];
        if(!w->used) //если никогда не приходили в эту вершину
        {
            strongconnect(*w, V, E); //рекурсивный запуск поиска в глубину
            v.lowlink = std::min(v.lowlink, w -> lowlink);
        }
        else if(w->on_stack) //если на стеке
            v.lowlink = std::min(v.lowlink, w -> global_idx);
    }

    //если вершина является корнем компоненты связности
    if(v.lowlink == v.global_idx)
    {
        uint32_t personal_idx;
        do //пока не дойдём до корня, выводим результаты
        {
            personal_idx = component.top(); //смотрим верх стека
            V[personal_idx].on_stack = 0; //убираем со стека
            component.pop();
            //чтобы посмотреть результаты надо расскоментировать std::cout
            //std::cout << personal_idx << ' ';
        }while(v.global_idx != V[personal_idx].global_idx);
        //std::cout << '\n';
    }
}

int main()
{
    uint32_t max_vertex = 300;
    uint32_t edge_amount = 0;
    uint32_t div = 5;

    //создаём массив вершин
    Vertex* V = new Vertex[max_vertex];

    //создаём массив рёбер
    std::vector<uint32_t>* E = new std::vector<uint32_t>[max_vertex];
    edge_generator(E, max_vertex, edge_amount, div);


    uint32_t avr_time = 0;
    uint32_t start_time;
    for(uint32_t j = 0; j < 1000; ++j)
    {
        //очищаем массив вершин
        for(uint32_t i = 0; i < max_vertex; ++i)
        {
            V[i].lowlink = 0;
            V[i].personal_idx = i;
            V[i].global_idx = 0;
            V[i].on_stack = 0;
            V[i].used = 0;
        }

        //начинаем прохождение по всем рёбрам
        
        start_time = clock();
        for(uint32_t i = 0; i < max_vertex; ++i)
            if(!V[i].used)
                strongconnect(V[i], V, E);
        avr_time += clock() - start_time;
    }

    std::cout << "Vertex: " << max_vertex << '\n';
    std::cout << "Edge: " << edge_amount << '\n';
    std::cout << "Edge exist%: " << div << '\n';
    std::cout << "avr(1000)time(s): " << avr_time / CLOCKS_PER_SEC << '\n';
    std::cout << "-----------\n";

    delete[] V;
    delete[] E;

    return 0;
}
