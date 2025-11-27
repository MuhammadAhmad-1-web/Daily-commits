# Dataset
traffic_logs = [
    "id:501,zone:A1,vehicle:Car,speed:62,time:08:30,violations:[None],status:Smooth",
    "id:502,zone:A1,vehicle:Bike,speed:85,time:09:10,violations:[Helmet],status:Busy",
    "id:503,zone:B2,vehicle:Bus,speed:45,time:17:25,violations:[None],status:Smooth",
    "id:504,zone:C3,vehicle:Car,speed:110,time:14:15,violations:[Overspeed],status:Congested",
    "id:505,zone:A1,vehicle:Truck,speed:40,time:18:50,violations:[None],status:Smooth"
]

# Question 1: Convert each traffic log into structured Python data with validation

def parse_traffic_log(log):
    """Parse a single traffic log string into a dictionary"""
    data = {}
    parts = log.split(',')
    
    for part in parts:
        if ':' in part:
            key, value = part.split(':', 1)
            
            # Clean up the key and value
            key = key.strip()
            value = value.strip()
            
            # Convert speed to integer
            if key == 'speed':
                data[key] = int(value)
            # Handle violations (remove brackets)
            elif key == 'violations':
                value = value.replace('[', '').replace(']', '')
                data[key] = value if value != 'None' else None
            else:
                data[key] = value
    
    return data

structured_data = [parse_traffic_log(log) for log in traffic_logs]

print("Q1: Structured Traffic Data")
print("=" * 60)
for entry in structured_data:
    print(entry)
print("\n")

# Question 2: Calculate average speed per zone

def calculate_avg_speed_per_zone(data):
    """Calculate average speed for each zone"""
    zone_speeds = {}
    
    for entry in data:
        zone = entry['zone']
        speed = entry['speed']
        
        if zone not in zone_speeds:
            zone_speeds[zone] = []
        zone_speeds[zone].append(speed)
    
    avg_speeds = {}
    for zone, speeds in zone_speeds.items():
        avg_speeds[zone] = sum(speeds) / len(speeds)
    
    return avg_speeds

avg_speed_per_zone = calculate_avg_speed_per_zone(structured_data)

print("Q2: Average Speed Per Zone")
print("=" * 60)
for zone, avg in avg_speed_per_zone.items():
    print(f"Zone {zone}: {avg:.2f} km/h")
print("\n")

# Question 3: Determine peak hour (hour with highest traffic entries)

def find_peak_hour(data):
    """Find the hour with most traffic entries"""
    hour_counts = {}
    
    for entry in data:
        time = entry['time']
        hour = int(time.split(':')[0])
        
        if hour not in hour_counts:
            hour_counts[hour] = 0
        hour_counts[hour] += 1
    
    peak_hour = max(hour_counts, key=hour_counts.get)
    return peak_hour, hour_counts

peak_hour, hour_counts = find_peak_hour(structured_data)

print("Q3: Peak Hour Analysis")
print("=" * 60)
print(f"Peak Hour: {peak_hour}:00 (with {hour_counts[peak_hour]} entries)")
print(f"All Hours: {hour_counts}")
print("\n")

# Question 4: Find vehicles with speed > 80 km/h

def find_overspeeding_vehicles(data, threshold=80):
    """Find vehicles exceeding speed threshold"""
    overspeeding = []
    
    for entry in data:
        if entry['speed'] > threshold:
            overspeeding.append({
                'id': entry['id'],
                'vehicle': entry['vehicle'],
                'speed': entry['speed'],
                'zone': entry['zone']
            })
    
    return overspeeding

overspeeding = find_overspeeding_vehicles(structured_data)

print("Q4: Vehicles with Speed > 80 km/h")
print("=" * 60)
for vehicle in overspeeding:
    print(f"ID: {vehicle['id']}, Type: {vehicle['vehicle']}, Speed: {vehicle['speed']} km/h, Zone: {vehicle['zone']}")
print("\n")

# Question 5: Count occurrences of each violation type

def count_violations(data):
    """Count each type of violation"""
    violation_counts = {}
    
    for entry in data:
        violation = entry['violations']
        
        if violation and violation != 'None':
            if violation not in violation_counts:
                violation_counts[violation] = 0
            violation_counts[violation] += 1
    
    return violation_counts

violation_counts = count_violations(structured_data)

print("Q5: Violation Count")
print("=" * 60)
for violation, count in violation_counts.items():
    print(f"{violation}: {count}")
print("\n")

# Question 6: Compute safety index for each zone

def compute_safety_index(data):
    """
    Safety Index = (Total Entries - Violations - Congested) / Total Entries * 100
    Higher index = Safer zone
    """
    zone_stats = {}
    
    for entry in data:
        zone = entry['zone']
        
        if zone not in zone_stats:
            zone_stats[zone] = {'total': 0, 'violations': 0, 'congested': 0}
        
        zone_stats[zone]['total'] += 1
        
        if entry['violations'] and entry['violations'] != 'None':
            zone_stats[zone]['violations'] += 1
        
        if entry['status'] == 'Congested':
            zone_stats[zone]['congested'] += 1
    
    safety_indices = {}
    for zone, stats in zone_stats.items():
        safe_entries = stats['total'] - stats['violations'] - stats['congested']
        safety_indices[zone] = (safe_entries / stats['total']) * 100
    
    return safety_indices

safety_indices = compute_safety_index(structured_data)

print("Q6: Safety Index Per Zone")
print("=" * 60)
for zone, index in safety_indices.items():
    print(f"Zone {zone}: {index:.2f}%")
print("\n")

# Question 7: Create a summary for each vehicle category

def vehicle_summary(data):
    """Create summary statistics for each vehicle type"""
    vehicle_stats = {}
    
    for entry in data:
        vehicle = entry['vehicle']
        
        if vehicle not in vehicle_stats:
            vehicle_stats[vehicle] = {
                'count': 0,
                'total_speed': 0,
                'violations': 0
            }
        
        vehicle_stats[vehicle]['count'] += 1
        vehicle_stats[vehicle]['total_speed'] += entry['speed']
        
        if entry['violations'] and entry['violations'] != 'None':
            vehicle_stats[vehicle]['violations'] += 1
    
    # Calculate averages
    summary = {}
    for vehicle, stats in vehicle_stats.items():
        summary[vehicle] = {
            'count': stats['count'],
            'avg_speed': stats['total_speed'] / stats['count'],
            'violations': stats['violations']
        }
    
    return summary

vehicle_summary_data = vehicle_summary(structured_data)

print("Q7: Vehicle Category Summary")
print("=" * 60)
for vehicle, stats in vehicle_summary_data.items():
    print(f"{vehicle}:")
    print(f"  Count: {stats['count']}")
    print(f"  Avg Speed: {stats['avg_speed']:.2f} km/h")
    print(f"  Violations: {stats['violations']}")
print("\n")

# Question 8: Identify high-congestion zones

def identify_congestion_zones(data):
    """Identify zones with congestion issues"""
    zone_congestion = {}
    
    for entry in data:
        zone = entry['zone']
        
        if zone not in zone_congestion:
            zone_congestion[zone] = {'total': 0, 'congested': 0}
        
        zone_congestion[zone]['total'] += 1
        
        if entry['status'] == 'Congested':
            zone_congestion[zone]['congested'] += 1
    
    # Calculate congestion percentage
    high_congestion = []
    for zone, stats in zone_congestion.items():
        congestion_rate = (stats['congested'] / stats['total']) * 100
        if congestion_rate > 0:  # Any congestion
            high_congestion.append({
                'zone': zone,
                'rate': congestion_rate,
                'congested_entries': stats['congested']
            })
    
    return sorted(high_congestion, key=lambda x: x['rate'], reverse=True)

high_congestion_zones = identify_congestion_zones(structured_data)

print("Q8: High-Congestion Zones")
print("=" * 60)
for zone_data in high_congestion_zones:
    print(f"Zone {zone_data['zone']}: {zone_data['rate']:.1f}% congestion ({zone_data['congested_entries']} entries)")
print("\n")

# Question 9: Classify each log into time windows (Morning, Afternoon, Evening, Night)

def classify_time_window(time):
    """Classify time into Morning/Afternoon/Evening/Night"""
    hour = int(time.split(':')[0])
    
    if 5 <= hour < 12:
        return "Morning"
    elif 12 <= hour < 17:
        return "Afternoon"
    elif 17 <= hour < 21:
        return "Evening"
    else:
        return "Night"

def add_time_windows(data):
    """Add time window classification to each entry"""
    for entry in data:
        entry['time_window'] = classify_time_window(entry['time'])
    return data

structured_data = add_time_windows(structured_data)

print("Q9: Time Window Classification")
print("=" * 60)
for entry in structured_data:
    print(f"ID {entry['id']}: {entry['time']} → {entry['time_window']}")
print("\n")

# Question 10: Generate final zone-level report

def generate_zone_report(data):
    """Generate comprehensive zone-level report"""
    zone_report = {}
    
    for entry in data:
        zone = entry['zone']
        
        if zone not in zone_report:
            zone_report[zone] = {
                'total_vehicles': 0,
                'speeds': [],
                'violations': [],
                'vehicle_types': {}
            }
        
        zone_report[zone]['total_vehicles'] += 1
        zone_report[zone]['speeds'].append(entry['speed'])
        
        if entry['violations'] and entry['violations'] != 'None':
            zone_report[zone]['violations'].append(entry['violations'])
        
        vehicle = entry['vehicle']
        if vehicle not in zone_report[zone]['vehicle_types']:
            zone_report[zone]['vehicle_types'][vehicle] = 0
        zone_report[zone]['vehicle_types'][vehicle] += 1
    
    # Process final report
    final_report = {}
    for zone, stats in zone_report.items():
        avg_speed = sum(stats['speeds']) / len(stats['speeds'])
        common_vehicle = max(stats['vehicle_types'], key=stats['vehicle_types'].get)
        
        # Safety category
        violation_rate = len(stats['violations']) / stats['total_vehicles']
        if violation_rate == 0:
            safety_category = "Safe"
        elif violation_rate < 0.5:
            safety_category = "Moderate"
        else:
            safety_category = "High Risk"
        
        final_report[zone] = {
            'total_vehicles': stats['total_vehicles'],
            'avg_speed': round(avg_speed, 2),
            'total_violations': len(stats['violations']),
            'common_vehicle': common_vehicle,
            'safety_category': safety_category
        }
    
    return final_report

zone_report = generate_zone_report(structured_data)

print("Q10: Final Zone-Level Report")
print("=" * 60)
for zone, report in zone_report.items():
    print(f"\nZone: {zone}")
    print(f"  Total Vehicles: {report['total_vehicles']}")
    print(f"  Average Speed: {report['avg_speed']} km/h")
    print(f"  Total Violations: {report['total_violations']}")
    print(f"  Most Common Vehicle: {report['common_vehicle']}")
    print(f"  Safety Category: {report['safety_category']}")

print("\n" + "=" * 60)
print("ANALYSIS COMPLETE!")
print("=" * 60)
