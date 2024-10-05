



// PM_1200_DP_CH_E_AND_CP_1ABC
var panel = msg.payload[0]
var power_meter = msg.payload[1]
var total_watt = msg.payload[2]
if (panel === "DP_CH_E" && power_meter === "PM_200"){
    msg.topic = "INSERT INTO table_pm200_data_total_watt (id, power_meter, total_watt) values(null, '" + power_meter + "','" + total_watt + "');"
    return msg;
}
if (panel === "DP_CH_E" && power_meter === "PM_220") {
    msg.topic = "INSERT INTO table_pm220_data_total_watt (id, power_meter, total_watt) values(null, '" + power_meter + "','" + total_watt + "');"
    return msg;
}

if (panel === "DP_CP_1ABC" && power_meter === "PM_200"){
    msg.topic = "INSERT INTO table_pm200_data_total_watt (id, power_meter, total_watt) values(null, '" + power_meter + "','" + total_watt + "');"
    return msg;
}
if (panel === "DP_CP_1ABC" && power_meter === "PM_220") {
    msg.topic = "INSERT INTO table_pm220_data_total_watt (id, power_meter, total_watt) values(null, '" + power_meter + "','" + total_watt + "');"
    return msg;
}




// PM_2100_DP_CH_E_AND_CP_1ABC
var panel = msg.payload[0]
var power_meter = msg.payload[1]
var total_watt = msg.payload[2]
if (panel === "DP_CH_E" && power_meter === "PM_200"){
    msg.topic = "INSERT INTO table_pm200_data_total_watt (id, power_meter, total_watt) values(null, '" + power_meter + "','" + total_watt + "');"
    return msg;
}
if (panel === "DP_CH_E" && power_meter === "PM_220") {
    msg.topic = "INSERT INTO table_pm220_data_total_watt (id, power_meter, total_watt) values(null, '" + power_meter + "','" + total_watt + "');"
    return msg;
}

if (panel === "DP_CP_1ABC" && power_meter === "PM_200"){
    msg.topic = "INSERT INTO table_pm200_data_total_watt (id, power_meter, total_watt) values(null, '" + power_meter + "','" + total_watt + "');"
    return msg;
}
if (panel === "DP_CP_1ABC" && power_meter === "PM_220") {
    msg.topic = "INSERT INTO table_pm220_data_total_watt (id, power_meter, total_watt) values(null, '" + power_meter + "','" + total_watt + "');"
    return msg;
}
