import time
import random

# Valores atuais
map_value = 0
injection_time = 0
tps_position = 0
coolant_temp = 0
lambda_afr = 0
duty_cycle = 0
battery_voltage = 0

# Valores mínimos e máximos
max_map_value = float('-inf')
max_injection_time = float('-inf')
max_tps_position = float('-inf')
max_coolant_temp = float('-inf')
max_lambda_afr = float('-inf')
max_duty_cycle = float('-inf')
max_battery_voltage = float('-inf')

min_map_value = float('inf')
min_injection_time = float('inf')
min_tps_position = float('inf')
min_coolant_temp = float('inf')
min_lambda_afr = float('inf')
min_duty_cycle = float('inf')
min_battery_voltage = float('inf')

def monitor_values():
    global map_value, injection_time, tps_position, coolant_temp, lambda_afr, duty_cycle, battery_voltage
    global max_map_value, max_injection_time, max_tps_position, max_coolant_temp, max_lambda_afr, max_duty_cycle, max_battery_voltage
    global min_map_value, min_injection_time, min_tps_position, min_coolant_temp, min_lambda_afr, min_duty_cycle, min_battery_voltage

    
      

        # Atualiza os valores mínimos
    min_map_value = min(min_map_value, map_value)
    min_injection_time = min(min_injection_time, injection_time)
    min_tps_position = min(min_tps_position, tps_position)
    min_coolant_temp = min(min_coolant_temp, coolant_temp)
    min_lambda_afr = min(min_lambda_afr, lambda_afr)
    min_duty_cycle = min(min_duty_cycle, duty_cycle)
    min_battery_voltage = min(min_battery_voltage, battery_voltage)
    max_map_value = max(max_map_value, map_value)
    max_injection_time = max(max_injection_time, injection_time)
    max_tps_position = max(max_tps_position, tps_position)
    max_coolant_temp = max(max_coolant_temp, coolant_temp)
    max_lambda_afr = max(max_lambda_afr, lambda_afr)
    max_duty_cycle = max(max_duty_cycle, duty_cycle)
    max_battery_voltage = max(max_battery_voltage, battery_voltage)

        
       

# Inicia o monitoramento dos valores
monitor_values()
