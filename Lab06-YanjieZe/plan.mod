/*********************************************
 * OPL 12.9.0.0 Model
 * Author: zyj
 * Creation Date: 2021年4月4日 at 下午7:36:42
 *********************************************/

 {string} Prod=...;
 {string} Process = ...;
 float ProfitProd[Prod]=...;
 
 int NbMonths = ...;
 range month=1..NbMonths;
 float ProcessProd[Process][Prod]=...;
 int MarketProd[month][Prod]=...;
 
 float CostHold = ...;
 int StartHold = ...;
 int EndHold = ...;
 int MaxHold = ...;
 
 int HoursMonth = ...;
 int NumProcess[Process]=...;
 int NumDown[Process]=...;
 
 int machines = 4+2+3+1+1;
 range machine_num = 1..machines;
 
 dvar boolean maintenance[month][machine_num];
 dvar int+ product_make[month][Prod];
 dvar int+ product_sell[month][Prod];
 
 
 dexpr float selling_profit = sum(m in month) sum(p in Prod)product_sell[m][p]*ProfitProd[p];

 dexpr float holding_cost = sum(m in month) sum(p in Prod) (product_make[m][p]-product_sell[m][p])*CostHold;
 
 dexpr float net_profit=selling_profit-holding_cost;
 
 maximize net_profit;
 subject to
 {
 forall(machine in machine_num)
   maintain_machine:
   	sum(m in month)maintenance[m][machine] == 5;

forall(p in Prod){
  forall(m in month)
    basic_hold: product_make[m][p]-product_sell[m][p] >= 0;
	
	final_hold: product_make[6][p]-product_sell[6][p] == EndHold;	
}

 forall(m in month){
   make_limit:{
   sum(p in Prod)product_make[m][p]*ProcessProd["Grind"][p] <= HoursMonth* (maintenance[m][1]+maintenance[m][4]+maintenance[m][2]+maintenance[m][3]);
   sum(p in Prod)product_make[m][p]*ProcessProd["VDrill"][p] <= HoursMonth* (maintenance[m][5]+maintenance[m][6]);
   sum(p in Prod)product_make[m][p]*ProcessProd["HDrill"][p] <= HoursMonth* (maintenance[m][7]+maintenance[m][8]+maintenance[m][9]);
   sum(p in Prod)product_make[m][p]*ProcessProd["Bore"][p] <= HoursMonth* (maintenance[m][10]);
   sum(p in Prod)product_make[m][p]*ProcessProd["Plane"][p] <= HoursMonth* (maintenance[m][11]);
 }   
 
 store_limit:
 	forall(p in Prod)product_make[m][p]-product_sell[m][p] <= MaxHold;
  
 sell_limit:
 	forall(p in Prod)product_sell[m][p] <= MarketProd[m][p];
}
 
} 
  
 
 
 