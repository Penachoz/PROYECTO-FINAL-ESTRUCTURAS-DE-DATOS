export class Equipo{

    constructor(nombre, soluciones, tiempo){
        this.nombre = nombre;
        this.soluciones = soluciones;
        this.tiempo = tiempo;
    }

    toString(){
        return "\n\tNombre: " + this.nombre +
        "\n\tFrecuencia: " + this.frecMensual;
    }
}