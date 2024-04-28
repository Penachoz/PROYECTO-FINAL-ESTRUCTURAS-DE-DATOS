import {Equipo} from './Equipo.js';
const salida = document.getElementById("TextArea1");
document.addEventListener('DOMContentLoaded', () => {
    const btnIngresar = document.getElementById("BotonIngresar");
    const btnConsultar = document.getElementById("BotonConsultar");

    btnIngresar.addEventListener('click',main);
    btnConsultar.addEventListener('click',desplegarReporte);
  });

const sortBySec = (a, b) => {
    if (a[1] !== b[1]) {
      return b[1] - a[1]; // order by most problems first
    } else {
      if (a[2] !== b[2]) {
        return a[2] - b[2]; // order by least time taken first (in case of tie)
      } else {
        return a[0].localeCompare(b[0]); // order alphabetically (in case of tie)
      }
    }
  }
  let info = [];
  let obj;
  function main (){
    let TextBox = document.getElementById("InputDatos");
    const datos = TextBox.value;
    const separatedByLines = datos.split(';');
    const separatedByWords = [];
  
    separatedByLines.forEach(line => {
      separatedByWords.push(line.split(' '));
    });
  
    let curTeam, curPro, time = 0;
    const results = [];
  
    for (let i = 0; i < separatedByWords.length; i++) {
      time = 0;
      if (separatedByWords[i][3] === 'C') {
        curTeam = separatedByWords[i][0];
        curPro = separatedByWords[i][1];
        time = parseInt(separatedByWords[i][2]);
        for (let j = i - 1; j >= 0; j --) {
          if (curTeam === separatedByWords[j][0] && separatedByWords[j][3] === 'I' && curPro === separatedByWords[j][1]) {
            time += 20;
          }
        }
  
        results.push(curTeam);
        results.push(time.toString());
      }
    }
  
    const solutions = [];
    let solucionados = 0;
  
    for (let i = 0; i < results.length; i += 2) {
      time = parseInt(results[i + 1]);
      solucionados = 1;
  
      for (let j = i + 2; j < results.length; j += 2) {
        if (results[i] === results[j] && results[j] !== 'VER') {
          results[j] = 'VER';
          solucionados++;
          time += parseInt(results[j + 1]);
        }
      }
  
      if (results[i] !== 'VER') {
        solutions.push([results[i], solucionados, time]);
      }
    }
  
    solutions.sort(sortBySec);
  
    for (let i = 0; i < solutions.length; i++) {
        obj = new Equipo(solutions[i][0], solutions[i][1], solutions[i][2]);
        info.push(obj);
    }
  }
  function desplegarReporte() {
    if (info.length === 0) {
      salida.value = "No data to display.";
    } else {
      const report = info.map(e => `${e.nombre} ${e.soluciones} ${e.tiempo}`).join("\n");
      salida.value = report;
    }
  }