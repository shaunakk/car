
#include <LiquidCrystal.h>
int hrs=0;
int mins=0;
int secs=0;
LiquidCrystal lcd(12,11,5,4,7,2);
void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Welcome!");
  delay(2000);
  lcd.clear();
  lcd.print("By Shaunak Kale");
  delay(4000);

}

void loop()
{
  lcd.setCursor(0,0);
  lcd.print("Vehicle Stopped");
  lcd.setCursor(0,1);
  lcd.print("UPTIME: ");
  secs=millis()/1000;
  hrs=secs/3600;
  mins=secs/60;
  if(hrs<10)lcd.print("0");
  lcd.print(hrs);
  lcd.print(":");
  mins=(secs%3600)/60;
  if(mins<10) lcd.print("0");
  lcd.print(mins);
  lcd.print(":");
  if(secs%60<10) lcd.print("0");
  lcd.print(secs%60);
}
