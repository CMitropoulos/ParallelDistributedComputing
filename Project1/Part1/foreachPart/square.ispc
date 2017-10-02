
static const float error = 0.00001;


export void calRoot_ispc(uniform double times, uniform float values[], uniform float result[], uniform float firstGuess){

    foreach(i = 0 ... times){
        
        double x1 = -1.0;
        double x0 = -1.0;

        x0 = firstGuess;
        do{
            x1 = (x0 - (((x0 * x0) - values[i]) / (2 * x0)));
            x0 = x1;
        }while((x1 * x1) - values[i] > 1e-4);

        result[i] = x1;
    }
   
}
