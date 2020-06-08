// pini za LED-ike
int LedNatakanje = 8;
int LedOdtekanje = 9;
// pini za tipke
int tipkaPolnjenje = 10;
int tipkaPraznjenje = 11;
// pin za svetlobni senzor
int senzorZgornji = A0;
// pin za toplotni senzor
int senzorSpodnji = A1;

// nižja vrednost predstavlja manj svetlobe (začelo se bo natakanje, ko bo brana vrednost majnša ali enaka tej meji)
const int mejaSvetlobni = 300;
// nižja vrednost predstavlja nižjo temperaturo (začelo se bo odtekanje, ko bo brana vrednost večja ali enaka tej meji)
const int mejaToplotni = 850;

int svetlobniVal = 0;
int toplotniVal = 0;

void setup() 
{
  pinMode(LedNatakanje, OUTPUT);
  pinMode(LedOdtekanje, OUTPUT);
  pinMode(tipkaPolnjenje, INPUT_PULLUP);
  pinMode(tipkaPraznjenje, INPUT_PULLUP);
  pinMode(senzorZgornji, INPUT);
  pinMode(senzorSpodnji, INPUT);
  // ta koda bo šla na koncu ven
  Serial.begin(9600);
  // -----------------------------
}

void loop() 
{
  svetlobniVal = analogRead(senzorZgornji);
  toplotniVal = analogRead(senzorSpodnji);
  int svetlobniVal = analogRead(senzorZgornji);
  int toplotnaVal = analogRead(senzorSpodnji);
  Serial.print("Svetlobni: ");
  Serial.println(svetlobniVal);
  Serial.print("Toplotni: ");
  Serial.println(toplotnaVal);
  delay(100);
    
  // ročno polni
  if (digitalRead(tipkaPolnjenje) == LOW)
  {
    odpri();
  }
  // ročno prazni
  else if (digitalRead(tipkaPraznjenje) == LOW)
  {
    zapri();
  }
  // praznjenje in polnjenje ni kontrolirano ročno
  else
  {
    // ko je senzor pokrit (manj svetlobe) je voda prišla čez zgornjo mejo
    if(nadZgornjimNivojem())
    {
      zapri();
    }
    // voda je prišla pod spodnjo mejo kadar je temperatura previsoka (senzor je segret)
    else if (podSpodnjimNivojem())
    {
      odpri();
    }
  }
}

// prižge lučko, ki predstavlja natakanje in ugasne lučko, ki predstavlja odtekanje, če je dovoljeno
void odpri()
{
  Serial.println("natakaj");
  // če ni nad zgornjim nivojem, se lahko nataka
  if (!nadZgornjimNivojem())
  {
    digitalWrite(LedNatakanje, HIGH);
    digitalWrite(LedOdtekanje, LOW);
  }
}
// prižge odtekanje in ugasne natakanje, če je dovoljeno
void zapri()
{
  Serial.println("odtekaj");
  // odteka v primeru, da ni pod spodnjo mejo
  if(!podSpodnjimNivojem())
  {
    digitalWrite(LedOdtekanje, HIGH);
    digitalWrite(LedNatakanje, LOW);
  }
}

bool nadZgornjimNivojem()
{
    // ko je senzor pokrit (manj svetlobe) je voda prišla čez zgornjo mejo
    if(svetlobniVal <= mejaSvetlobni)
    {
      return true;
    }
    return false;
}
bool podSpodnjimNivojem()
{
    // voda je prišla pod spodnjo mejo kadar je temperatura previsoka (senzor je segret)
    if (toplotniVal >= mejaToplotni)
    {
      return true;
    }
    return false;
}
