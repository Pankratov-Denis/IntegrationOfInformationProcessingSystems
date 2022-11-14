#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>
#include <stack>
#include <map>
#include <limits>

//представление графа в виде списка смежности

//константа под определиение бесконечности
const int INF = std::numeric_limits<int>::max();

//ребро
struct Edge
{
    int weight; //вес ребра
    int indexTo; //на какую вершину оно направлено
};

//вершины
struct  Node
{
    int id; //id
    std::vector<Edge> edges; //список рёбер

    int prevIndex; //предыдущий индех
    int weight;    //вес пути
    bool visited;  //посещалась ли вершина
};

// граф
struct Graph
{
    std::vector<Node> nodes; // вершины

    void clear() //очистка всего графа
    {
        nodes.clear();
    }

    //очистка списка рёбер
    void clear_edges()
    {
        for(auto& node : nodes)
        {
            node.edges.clear();
        }
    }

    //иничиализация стартовых параметров
    void init_start_values()
    {
        for(auto& node : nodes)
        {
            node.weight = INF; 
            node.visited = false;
            node.prevIndex = INF;
        }
    }
};

bool read_nodes(std::istream& istream, int nodes_count, Graph& graph_out)
{
    graph_out.nodes.clear();
    for (int i = 0; i < nodes_count; i++)
    {
        decltype(Node::id) id;
        istream >> id;
        graph_out.nodes.push_back({id});
    }
    return true;
}

bool read_edges(std::istream& istream, int edges_count, Graph& graph_out)
{
    graph_out.clear_edges();

    for (int i = 0; i < edges_count; i++)
    {
        int start_id, end_id;
        int weight;

        istream >> start_id >> end_id;
        istream >> weight;

        auto& nodes_ref = graph_out.nodes;

        //валидны ли данные рёбра, ищем начало и конец
        auto start_iter = std::find_if(nodes_ref.begin(),nodes_ref.end(),[start_id](const auto& node){return node.id == start_id;});
        auto end_iter = std::find_if(nodes_ref.begin(),nodes_ref.end(),[end_id](const auto& node){return node.id == end_id;});

        //если не нашли, то выходим
        if(start_iter == nodes_ref.end() || end_iter == nodes_ref.end())
        {
            graph_out.clear_edges();
            return false;
        }
        //заносим новое ребро
        int index = (end_iter - nodes_ref.begin());
        (*start_iter).edges.push_back(Edge{ weight, index });

    } 
    return true;  
}

Graph read_graph(const std::string& file_path)
{
    Graph graph;
    std::ifstream fin(file_path);
    if (fin)
    {
        int node_count;
        int edge_count;

        fin >> node_count >> edge_count;

        if (read_nodes(fin, node_count, graph))
        {
            read_edges(fin, edge_count, graph);
        }
    }
    return graph;
}

std::vector<int> convert_graph_to_path(Graph& graph, int start_index, int end_index)
{
    std::vector<int> result;
    std::stack<int> tmp_path;
    int current_node = end_index;
    //от конечной вершины к начальной
    while (current_node != INF)
    {
        tmp_path.push(current_node);
        current_node = graph.nodes[current_node].prevIndex;
    }
    //стек обратно в массив в нормальном порядке
    while (!tmp_path.empty())
    {
        result.push_back(tmp_path.top());
        tmp_path.pop();
    }
    return result;
}

std::vector<int> find_path_Dijkstra(Graph& graph, int start_index, int end_index)
{
    graph.init_start_values();
    std::map<int, int> min_weigth_map;
    graph.nodes[start_index].weight = 0;
    min_weigth_map[0] = start_index;
    //min_weigth_map.insert({ 0, start_index });
    while (!min_weigth_map.empty())
    {
        auto [current_weight, current_index] = *(min_weigth_map.begin());
        min_weigth_map.erase(min_weigth_map.begin());

        //если вершина посешена
        if (graph.nodes[current_index].visited)
        {
            continue;
        }

        graph.nodes[current_index].visited = true;

        for (int i = 0; i < graph.nodes[current_index].edges.size(); i++)
        {
            int index_to = graph.nodes[current_index].edges[i].indexTo;  //куда ведёт ребро
            int edged_weight = graph.nodes[current_index].edges[i].weight; //вес вершины куда ведёт ребро
            //если вершина не посещена
            if (!graph.nodes[index_to].visited)
            {
                //если вес меньше, чем уже найденный
                if (current_weight + edged_weight < graph.nodes[index_to].weight )
                {
                    graph.nodes[index_to].weight = current_weight + edged_weight;
                    graph.nodes[index_to].prevIndex = current_index;
                    min_weigth_map [graph.nodes[index_to].weight] =  index_to;
                }
            }
        }

    }

    return convert_graph_to_path(graph, start_index, end_index);
}

int main()
{
    auto graph = read_graph("input.txt");
    auto path = find_path_Dijkstra(graph, 0, 4);

    for (auto path_node_index : path)
    {
        std::cout << graph.nodes[path_node_index].id << " ";
    }

    std::cout << std::endl;
}
