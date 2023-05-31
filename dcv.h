class DCV{
  int valve_out, valve_in;
  bool valState = LOW;
  int timer = -1;
  int duration = -1;
  public:
    DCV(int p1, int p2, int dur){
        valve_out = p1;
        valve_in = p2;
        duration = dur;
    }

    void reverse(valve_out, valve_in){
        digitalWrite(valve_out, LOW);
        valState = !valState;
        digitalWrite(valve_in, valState);
        digitalWrite(valve_out,!valState);
        timer = millis();        
    }

    bool rest()
    {
        if(timer < 0) return false;
        if(millis()-timer == duration){
        digitalWrite(valve_in, 0);
        digitalWrite(valve_out,0);
        return true;
        }  
       return false;
    }
};
