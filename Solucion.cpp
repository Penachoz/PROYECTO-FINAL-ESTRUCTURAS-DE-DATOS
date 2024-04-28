#include<bits/stdc++.h>
#include <sstream>
using namespace std;
bool sortbysec(const tuple<string, int, int>& a,const tuple<string, int, int>& b)
{
    if(get<1>(a)!=get<1>(b))
    return (get<1>(a) > get<1>(b));//El que mas problemas hizo
    else{
        if(get<2>(a)!=get<2>(b))
        return (get<2>(a) < get<2>(b));//El que menos tiempo obtuvo (en caso de empate del anterior criterio)
        else{
            return (get<0>(a) < get<0>(b));//Ordenamiento alfabetico (en caso de empate del anterior criterio)
        }
    }
}

int main()
{
    string Datos;
    getline(cin,Datos);// Aca recibiremos la cadena de 'Team1 1 5 C;Team2 5 10 C;Team3 2 15 I;Team1 3 20 R;Team2 1 25 R;Team2 4 30 C;Team1 3 35 I;Team1 3 40 C;Team3 2 45 I;Team3 2 50 C'
    //Es decir, (Equipo) (Numproblema) (Tiempo) (Estado), Posibles estados -> C, I;
    vector<string> Resultados;
    vector<string> SeparadoPorLineas;
    vector<tuple<string, int, int>> ans;
    istringstream ss(Datos);
    string linea;

    while (getline(ss, linea, ';')) {
    SeparadoPorLineas.push_back(linea);
    }
    //Una vez separado por ";", tenemos (Equipo) (Numproblema) (Tiempo) (Estado), seria repetir lo mismo pero con " "(espacios) y listo, tenemos separado todo
    vector<string> tokens;
    string token;
    for(auto linea : SeparadoPorLineas){
        istringstream sd(linea);
        while(getline(sd, token, ' ')){
            tokens.push_back(token);
        }
    }
    string curTeam; //Empezamos con el primer equipo
    string curPro;
    int time=0;
    for(int i = 0 ; i < tokens.size() ; i++)
    {
        time = 0;
        if(tokens[i]=="C")
        {
            curTeam = tokens[i-3];
            curPro = tokens[i-2];
            time += stoi(tokens[i-1]);
            for(int j = i-4 ; j >= 3 ; j--) // Estados estan en [3] [7]... [3+4n]
            {
                if(curTeam==tokens[j-3]&&tokens[j]=="I"&&curPro == tokens[j-2])time+=20;
            }
            //cout << curTeam << " " << curPro << " " << time << endl;
            Resultados.push_back(curTeam);
            Resultados.push_back(to_string(time));
        }
    }
    //for(auto i : Resultados) cout << i << endl;
    string lineaR; //Linea de resultado
    int solucionados;
    for(int i = 0 ; i < Resultados.size(); i+=2)
    {
        time=stoi(Resultados[i+1]);
        solucionados = 1;
        for(int j = i+2 ; j < Resultados.size() ; j++)
        {
            if(Resultados[i]==Resultados[j]&&Resultados[i]!="VER") // VER es que ya pasamos por ese equipo;
            {
                Resultados[j]="VER";//Cada vez que recorramos, volveresmo el Equipo = VER para que asi no repitamos equipos
                solucionados++;
                time+=stoi(Resultados[j+1]);
            }
        }
        if(Resultados[i]!="VER"){
                ans.push_back(make_tuple(Resultados[i], solucionados, time));//Metemos cada una solucion en una tupla, que luego entra en un vector de tuplas
        }
    }
    sort(ans.begin() , ans.end() , sortbysec);//Aqui mandamos a que se ordenen segun los criterios
    for(auto i : ans)cout << get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << endl;// Se imprime el resultado
}
