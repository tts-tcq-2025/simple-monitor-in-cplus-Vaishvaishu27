@@ -1,11 +1,13 @@

def is_within_limits(temperature, soc, charge_rate):
  return 0 <= temperature <= 45 and 20 <= soc <= 80 and charge_rate <= 0.8

def battery_is_ok(temperature, soc, charge_rate):
  if 0 <= temperature <= 45 and 20 <= soc <= 80 and charge_rate <= 0.8:
  if is_within_limits(temperature, soc, charge_rate):
    return True
    print('Temperature, State of Charge and Charge Rate is out of range!')
    return False
  
  print('Temperature, State of Charge and Charge Rate is out of range!')
  return False

if __name__ == '__main__':
  assert(battery_is_ok(25, 70, 0.7) is True)
  assert(battery_is_ok(50, 85, 0) is False)
  assert battery_is_ok(25, 70, 0.7) is True
  assert battery_is_ok(50, 85, 0) is False
