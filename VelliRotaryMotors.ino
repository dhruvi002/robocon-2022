#define outputA 2
#define outputB 3

int counter=0;
int acurrentstate;
int alaststate;

void setup()
{
  pinMode( outputA, OUTPUT);
  pinMode( outputB, OUTPUT);

  Serial.begin(9600);

  alaststate=digitalRead(outputA);
}

void loop()
{
  acurrentstate=digitalRead(outputA);
  if(acurrentstate != alaststate)
  {
    if(digitalRead(outputB)!=acurrentstate){
    counter ++;}
  else{
    counter --;}
  Serial.print("Position: ");
  Serial.println(counter);
  }
  alaststate=acurrentstate;
}
