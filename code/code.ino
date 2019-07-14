byte cols[] = { 2, 3, 4 };
const int rowCount = sizeof(rows)/sizeof(rows[0]);

byte rows[] = { 5, 6, 7, 8 };
const int colCount = sizeof(cols)/sizeof(cols[0]);

byte keys[colCount][rowCount];

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < rowCount; i++) {
    Serial.print(rows[i]); Serial.println(" : INPUT");
    pinMode(rows[i], INPUT);
  }
  
  for (int i = 0; i < colCount; i++) {
    Serial.print(cols[i]); Serial.println(" : INPUT_PULLUP");
    pinMode(cols[i], INPUT_PULLUP);
  }
}

void readMatrix() {
    // iterate the columns
    for (int colIndex=0; colIndex < colCount; colIndex++) {
        // col: set to output to low
        byte curCol = cols[colIndex];
        pinMode(curCol, OUTPUT);
        digitalWrite(curCol, LOW);
 
        // row: interate through the rows
        for (int rowIndex=0; rowIndex < rowCount; rowIndex++) {
            byte rowCol = rows[rowIndex];
            pinMode(rowCol, INPUT_PULLUP);
            keys[colIndex][rowIndex] = digitalRead(rowCol);
            pinMode(rowCol, INPUT);
        }
        // disable the column
        pinMode(curCol, INPUT);
    }
}
 
void printMatrix() {
    for (int rowIndex=0; rowIndex < rowCount; rowIndex++) {
        if (rowIndex < 10)
            Serial.print(F("0"));
        Serial.print(rowIndex); Serial.print(F(": "));
 
        for (int colIndex=0; colIndex < colCount; colIndex++) {  
            Serial.print(keys[colIndex][rowIndex]);
            if (colIndex < colCount)
                Serial.print(F(", "));
        }   
        Serial.println("");
    }
    Serial.println("");
}
 
void loop() {
    readMatrix();
    printMatrix();
    delay(1000);
}
