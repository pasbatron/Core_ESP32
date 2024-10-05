String dataIn;
String dt[10];
int i;
boolean parsing=false;
 
void parsingData(){
    int j=0;
    Serial.print("data masuk : ");
    Serial.print(dataIn);
    Serial.print("\n");
    dt[j]="";
    for(i=1;i<dataIn.length();i++){
    if ((dataIn[i] == '#') || (dataIn[i] == ',')){
        j++;
        dt[j]="";
    }else{
        dt[j] = dt[j] + dataIn[i];
    }
    }



    Serial.print("data 1 : ");
    Serial.print(dt[0]);
    Serial.print("\n");
    Serial.print("data 2 : ");
    Serial.print(dt[1].toInt());
    Serial.print("\n");
    Serial.print("data 3 : ");
    Serial.print(dt[2].toInt());
    Serial.print("\n");
    Serial.print("data 4 : ");
    Serial.print(dt[3].toInt());
    Serial.print("\n");
    Serial.print("data 5 : ");
    Serial.print(dt[4].toInt());
    Serial.print("\n\n");
}



void setup() {
    Serial.begin(9600);



    dataIn="";


}
 
void loop() {


    
    if(Serial.available()>0){
        char inChar = (char)Serial.read();
        dataIn += inChar;
        if (inChar == '\n') {parsing = true;}
    }if(parsing){
        parsingData();
        parsing=false;
        dataIn="";
    }
}
 

