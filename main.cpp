#include <iostream>
#include <random>
#include "(1+1)-EE.h"

int main() {
  int Gmax = 500;
  // (1.0,1.5) => x=(-0.089842,0.712656 ), f(x)=-1.031628 20000 lo mismo con (-1,1)
  // (-3.0,2.0) => x=(0.089842,-0.712656 ), f(x)=-1.031628, ps=0.000000 lo mismo con (1,1)
  // Probé con (1.0,1.5)
  std::vector<double> x{-3.0,2.0};
  const std::vector<std::pair<double, double>> constraints{std::make_pair(-3.0,3.0), std::make_pair(-2.0,2.0)};
  auto results = onePOneEE(Gmax, x, constraints, "(-3,2)Prueba.txt");

  // Crear reporte de estadisticas de 20 corridas
  /*std::ofstream report("report.txt");
  report << "Ejecución & $x_1$ & $x_2$ & $f(x)$ & Media & Varianza & Desviación estandar & Mejor & Peor & Gmax\\\\\n";
  std::random_device rd;  // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<double> disX(constraints[0].first, constraints[0].second);
  std::uniform_real_distribution<double> disY(constraints[1].first, constraints[1].second);
  for (int i = 0; i < 20; ++i) {

    // Generamos x y lo gurdamos ya que onePOneEE pasa valores por referencia
    x[0] = disX(gen);
    x[1] = disY(gen);
    auto xPrime = x;

    // f(x)
    double f = function(x);

    // Corremos estrategia evolutiva
    auto result = onePOneEE(Gmax, x, constraints, "reporte"+std::to_string(i+1)+".txt");

    // Media, min y max (mejor y peor)
    double avg = 0.0;
    double min = std::numeric_limits<double>::max();
    double max = std::numeric_limits<double>::min();
    for(auto &element: result){
      // buscar mínimo
      if(element.second < min){
        min = element.second;
      }
      // buscar máximo
      if(element.second > max){
        max = element.second;
      }

      avg += element.second;
    }
    avg /= (double) result.size();

    // Varianza y Desviación estandar
    double s2 = 0.0;
    for(auto &element: result){
      s2 += (element.second - avg)*(element.second - avg);
    }
    s2 /= (double) result.size();
    double dev = sqrt(s2);
    report << i+1 << " & " << xPrime[0] << " & " << xPrime[1] << " & $" << std::to_string(f) << "$ & $" << std::to_string(avg) << "$ & $" << std::to_string(s2) << "$ & $" << std::to_string(dev) << "$ & $" << std::to_string(min) << "$ & $" << std::to_string(max) << "$ & $" << Gmax << "$\\\\\n";
  }
  report.close();*/

  return 0;
}
