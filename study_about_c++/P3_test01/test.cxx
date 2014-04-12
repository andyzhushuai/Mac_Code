#include<iostream>
#include<stdio.h>

using namespace std;

int main()
{
	double P3[4][4][4][4][4][4];
	double G1[4][4];
	double Sum = 0.0;
	for(int i=0; i<4; i++)
	{
	   for(int j=0; j<4; j++)
	   {
	      if ((i==j)){if (i!=0)G1[i][j] = -1.0;else G1[i][j] = 0.0;}		//In center of mass frame,p_psi_x,p_psi_y,p_psi_z = 0,so G1[123][123] = -1, G1[0][0] = 0.
	      else G1[i][j] = 0.0;
//cout<<"haha: G1["<<i<<"]"<<"["<<j<<"] = " << G1[i][j] << endl;
	   }
	}
	
	for(int u=0; u<4; u++)
	{
	   for(int v=0; v<4; v++)
	   {
	      for(int lm=0; lm<4; lm++)
	      {
		 for(int up=0; up<4; up++)
		 {
		    for(int vp=0; vp<4; vp++)
		    {
		       for(int lmp=0; lmp<4; lmp++)
		       {
			  P3[u][v][lm][up][vp][lmp] = 0.0 - 1.0/6.0*(
					      G1[u][up]*G1[v][vp]*G1[lm][lmp] + G1[u][up]*G1[v][lmp]*G1[lm][vp] + G1[u][vp]*G1[v][up]*G1[lm][lmp] +
                                              G1[u][vp]*G1[v][lmp]*G1[lm][up] + G1[u][lmp]*G1[v][vp]*G1[lm][up] + G1[u][lmp]*G1[v][up]*G1[lm][vp]
								    )
							  + 1.0/15.0*(
					      G1[u][v]*G1[up][vp]*G1[lm][lmp] + G1[u][v]*G1[vp][lmp]*G1[lm][up] + G1[u][v]*G1[up][lmp]*G1[lm][vp] +
					      G1[u][lm]*G1[up][lmp]*G1[vp][v] + G1[u][lm]*G1[up][vp]*G1[v][lmp] + G1[u][lm]*G1[vp][lmp]*G1[v][up] +
					      G1[v][lm]*G1[vp][lmp]*G1[u][up] + G1[v][lm]*G1[up][vp]*G1[u][lmp] + G1[v][lm]*G1[up][lmp]*G1[u][vp]
								     );
//			  int Uni = int(P3[u][v][lm][up][vp][lmp]);
//			  Sum = Sum + P3[u][v][lm][up][vp][lmp];
			  if(P3[u][v][lm][up][vp][lmp]!=0)
			  {
			     cout<<"P3["<<u<<"]["<<v<<"]["<<lm<<"]["<<up<<"]["<<vp<<"]["<<lmp<<"] = "<<P3[u][v][lm][up][vp][lmp]<<";"<<endl;
			     Sum = Sum + P3[u][v][lm][up][vp][lmp];
			  }
//			  cout<<"P3["<<u<<"]["<<v<<"]["<<lm<<"]["<<up<<"]["<<vp<<"]["<<lmp<<"] = "<<P3[u][v][lm][up][vp][lmp]<<endl;
			 // printf("P3[%d][%d][%d][%d][%d][%d] = %f\n",u,v,lm,up,vp,lmp,P3[u][v][lm][up][vp][lmp]);
		       }
		    }
		 }
	      }
	   }
	}
			  printf("Sum = %f\n",Sum);
	
	return 0;
}
