static const float error = 0.00001;

task void
calRoot_launched(uniform double times,
		 uniform float values[],
		 uniform float result[],
		 uniform float firstGuess,
		 uniform int span){
    
    uniform int start = taskIndex * span;
    uniform int end = min((taskIndex+1) * span, (unsigned int)times);	
    foreach(i = start ... end){
        
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

export void calRoot_ispc(uniform double times,
                         uniform float values[],
                         uniform float result[],
                         uniform float firstGuess){

   uniform int span = 100;

   launch[times/span] calRoot_launched(times, values, result,firstGuess,span);
}


