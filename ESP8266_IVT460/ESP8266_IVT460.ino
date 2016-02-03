boolean debug=true;
const int NUMBER_OF_FIELDS = 37; // how many comma separated fields we expect
int fieldIndex = 0;            // the current field being received
int values[NUMBER_OF_FIELDS];   // array holding values for all the fields
boolean dataAvailable = false;

int sekvensummer;
int framledningstemperatur; //(GT1)
int utetemperatur; //(GT2)
int tappvarmvatten; //(GT3-1), dvs 47,8 grader
int varmvatten; //(GT3-2), dvs 44,5 grader
int varmevatten; //(GT3-3), dvs 44,7 grader
int rumstemperatur;//(GT5), men jag har inte den givaren så den visar -512
int hetgastemperatur;//(GT6), dvs 77,4 grader

void setup() {
   Serial.begin(9600);           // set up Serial library at 9600 bps
  // put your setup code here, to run once:

}

void loop() {
  checkSerialForData();
}

void checkSerialForData(){
 //check if there is serial data to parse
  
  if (Serial.available() > 0)
  {
    dataAvailable = true;
    if (debug == true)
    {
      Serial.println("data available triggered and debug mode active");
    }
  }
  boolean numberIsNegative = false;
  while (dataAvailable == true)
  {
    
    char ch = Serial.read();
    if (ch >= '0' && ch <= '9' || ch == '-' || ch == ' '){
    if (ch >= '0' && ch <= '9' || ch == '-' ) // is this an ascii digit between 0 and 9?
    {
      // yes, accumulate the value if the fieldIndex is within range
      // additional fields are not stored
      if (ch == '-'){
        numberIsNegative = true;
        }
      else if (fieldIndex < NUMBER_OF_FIELDS) {
        values[fieldIndex] = (values[fieldIndex] * 10) + (ch - '0');
      }

      if (debug==true){
      Serial.print("values[fieldIndex] for index ");
      Serial.print(fieldIndex);
      Serial.print(" is ");
      Serial.println(values[fieldIndex]);
      Serial.println(numberIsNegative);
      
      }
      }
    }
    else if (ch == ';')  // comma is our separator, so move on to the next field
    {
      if (numberIsNegative == true){
        values[fieldIndex] = (values[fieldIndex] * -1);
        numberIsNegative = false;
        }
      fieldIndex++;   // increment field index
    }
    else
    {
      //Set variables based on inpserut
      sekvensummer= values[0];
      framledningstemperatur= values[1];; //(GT1)
      utetemperatur= values[2];; //(GT2)
      tappvarmvatten= values[3];; //(GT3-1), dvs 47,8 grader
      varmvatten= values[4];; //(GT3-2), dvs 44,5 grader
      varmevatten= values[5];; //(GT3-3), dvs 44,7 grader
      rumstemperatur= values[6];;//(GT5), men jag har inte den givaren så den visar -512
      hetgastemperatur= values[7];;//(GT6), dvs 77,4 grader

      if (debug == true) {
        Serial.println("Serial data received.");
        Serial.print("sekvensummer: ");
        Serial.println(sekvensummer);
        Serial.print("framledningstemperatur: ");
        Serial.println(framledningstemperatur);
        Serial.print("utetemperatur: ");
        Serial.println(utetemperatur);
        Serial.print("tappvarmvatten: ");
        Serial.println(tappvarmvatten);
        Serial.print("varmvatten: ");
        Serial.println(varmvatten);
        Serial.print("varmevatten: ");
        Serial.println(varmevatten);
        Serial.print("rumstemperatur: ");
        Serial.println(rumstemperatur);
        Serial.print("hetgastemperatur: ");
        Serial.println(hetgastemperatur);
      }
      // print each of the stored fields

      for (int i = 0; i < min(NUMBER_OF_FIELDS, fieldIndex + 1); i++)
      {
        //Serial.println(values[i]);

        values[i] = 0; // set the values to zero, ready for the next message
      }

      fieldIndex = 0;  // ready to start over
      if (debug == true) {
      Serial.println("parametersProcessed data available set to false");
      }
      dataAvailable = false;
    }
  }
}
