task void srt(uniform float * nums, uniform float * roots, uniform int endindex, uniform int startindex){
  varying struct RNGState state;
   seed_rng(&state,500+programIndex);
//added start and end limitations to the partial arrays
	foreach(i=startindex...endindex)
    {float r1=random(&state);
	float r2=random(&state);
	float x=(min(r1,r2)/max(r1,r2))*8;
	
	float root=sqrt(x);
	//print("sqrt % ",x);
	nums[i]=x;
	float est=x;
	while ( abs(root-est)>.0001){
	
	   est=est-(est*est-x)/(2*est);
	   //print("error =%f",est-root);
	
	}
	roots[i]=est;
	//print("root % est %", root, est);
	}


}


export void sroot(uniform float  nums[], uniform float  roots[], uniform int size, uniform int ntasks){
  uniform int i=0;
    uniform int s=size/ntasks;
  while (i<ntasks-1){

  launch srt(&nums[s*i],&roots[s*i],s, s*i);
//passing s*i as well as s so the partial array can be delimited efficiently
  i=i+1;
  }
  launch srt(&nums[s*i],&roots[s*i],size-s*i, s*i);
  sync;

}

export void sr(uniform float  nums[], uniform float roots[], uniform int size){
  varying struct RNGState state;
   seed_rng(&state,500+programIndex);

	foreach(i=0...size)
    {float r1=random(&state);
	float r2=random(&state);
	float x=(min(r1,r2)/max(r1,r2))*8;
	
	float root=sqrt(x);
	//print("sqrt % ",x);
	nums[i]=x;
	float est=x;
	while ( abs(root-est)>.0001){
	
	   est=est-(est*est-x)/(2*est);
	   //print("error =%f",est-root);
	
	}
	roots[i]=est;
	//print("root % est %", root, est);
	}


}
