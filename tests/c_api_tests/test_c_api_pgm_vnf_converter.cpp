// SPDX-FileCopyrightText: Contributors to the Power Grid Model project <powergridmodel@lfenergy.org>
//
// SPDX-License-Identifier: MPL-2.0

#include <power_grid_model_io_native_c/basics.h>
#include <power_grid_model_io_native_c/handle.h>
#include <power_grid_model_io_native_c/pgm_vnf_converter.h>

#include <doctest/doctest.h>

#include <ostream> // NOLINT(misc-include-cleaner) // Windows Clang-Tidy issue
#include <string_view>

namespace power_grid_model_io_native {

namespace {
auto const* const basic_vision_9_7_vnf_file = R"vnf(V9.7
NETWORK

[PROPERTIES]
#System Currency:'$' 
#General 
#Invisible 
#History 
#HistoryItems 
#Users 
[]

[SHEET]
#General GUID:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' Name:'Sheet 1' Color:$00C0C0C0 
[]

[NODE]
#General GUID:'{7FF722ED-33B3-4761-84AC-A164310D3C86}' CreationTime:44875.5806865509 Name:'node1' Unom:11 
#Railtype 
#Installation Kb:0.5 Kt:1 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:14800 Y:14800 Symbol:1 Size:6 Width:4 UpstringsY:-70 FaultStringsX:-20 FaultStringsY:20 NoteX:5 NoteY:5 IconY:50 
#General GUID:'{1ED177A7-1F5D-4D81-8DE7-AB3E58512E0B}' CreationTime:44875.5937016435 Name:'node2' Unom:11 
#Railtype 
#Installation Kb:0.5 Kt:1 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:14940 Y:14800 Symbol:1 Size:6 Width:4 UpstringsY:-70 FaultStringsX:-20 FaultStringsY:20 NoteX:5 NoteY:5 IconY:50 
#General GUID:'{DDE3457B-DB9A-4DA9-9564-6F49E0F296BD}' CreationTime:44875.5965067593 Name:'node3' Unom:0.4 
#Railtype 
#Installation Kb:0.5 Kt:1 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15100 Y:14800 Symbol:1 Size:14 Width:4 UpstringsY:-150 FaultStringsX:-20 FaultStringsY:20 NoteX:5 NoteY:5 IconY:50 
#General GUID:'{A79AFDE9-4096-4BEB-AB63-2B851D7FC6D1}' CreationTime:44875.5989385185 Name:'node4' Unom:11 
#Railtype 
#Installation Kb:0.5 Kt:1 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15100 Y:15100 Symbol:1 Size:8 Width:4 UpstringsY:-90 FaultStringsX:-20 FaultStringsY:20 NoteX:5 NoteY:5 IconY:50 
#General GUID:'{7848DBC8-9685-452C-89AF-9AB308224689}' CreationTime:44886.4465440509 Unom:0.4 
#Railtype 
#Installation Kb:0.5 Kt:1 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15040 Y:14580 Symbol:1 Size:4 Width:4 UpstringsY:-50 FaultStringsX:-20 FaultStringsY:20 NoteX:5 NoteY:5 IconY:50 
[]

[LINK]
#General GUID:'{A4F61576-CFE1-4256-AF66-06AA0B7F5527}' CreationTime:44875.5943923958 Node1:'{7FF722ED-33B3-4761-84AC-A164310D3C86}' Node2:'{1ED177A7-1F5D-4D81-8DE7-AB3E58512E0B}' Name:'link1' SwitchState1:1 SwitchState2:1 RailConnectivity:1 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' Strings1X:12 Strings1Y:6 Strings2X:-15 Strings2Y:6 MidStringsY:4 FaultStringsX:-20 FaultStringsY:20 NoteY:5 FirstCorners:'{(14800 14860) }' SecondCorners:'{(14940 14860) }' 
[]

[LINE]
#General GUID:'{B9558FB9-D06D-4B4D-A43F-0504597BD575}' CreationTime:44875.5945847222 MutationDate:44886 Node1:'{7FF722ED-33B3-4761-84AC-A164310D3C86}' Node2:'{1ED177A7-1F5D-4D81-8DE7-AB3E58512E0B}' Name:'line1' SwitchState1:1 SwitchState2:1 
#LinePart R:0.002 X:0.008 C:0.5 R0:0.002 X0:0.008 C0:0.5 Inom1:1000 Inom2:1000 Inom3:1000 TR:30 Length:500 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' Strings1X:12 Strings1Y:6 Strings2X:-15 Strings2Y:6 MidStringsY:4 FaultStringsX:-20 FaultStringsY:20 NoteY:5 FirstCorners:'{(14800 14780) }' SecondCorners:'{(14940 14780) }' 
[]

[CABLE]
#General GUID:'{2FF748A9-78F3-4145-9E08-2CAEA5658F82}' CreationTime:44875.5938880671 Node1:'{7FF722ED-33B3-4761-84AC-A164310D3C86}' Node2:'{1ED177A7-1F5D-4D81-8DE7-AB3E58512E0B}' Name:'cable1' SwitchState1:1 SwitchState2:1 DynModel:'P' DynSection:1 
#CablePart Length:123 ParallelCableCount:1 CableType:'10.5kV 3x240mm² Al XLPE' GroundResistivityIndex:2 AmpacityFactor:2 
#CableType ShortName:'240 Al X' Unom:10 R:0.162 X:0.089 C:0.45 TanDelta:0.0004 R0:0.68 X0:0.339 C0:0.45 Inom0:455 G1:0.5 Inom1:399 G2:0.75 Inom2:360 G3:1 Inom3:342 Ik1s:22.8 TR:90 TInom:90 TIk1s:250 Frequency:50 PulseVelocity:150 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' Strings1X:12 Strings1Y:6 Strings2X:-15 Strings2Y:6 MidStringsY:4 FaultStringsX:-20 FaultStringsY:20 NoteY:5 FirstCorners:'{(14800 14740) }' SecondCorners:'{(14940 14740) }' 
[]

[TRANSFORMER]
#General GUID:'{D783FB03-DAF4-4471-B1AC-B74451717DF4}' CreationTime:44875.5968281481 MutationDate:45463 Node1:'{1ED177A7-1F5D-4D81-8DE7-AB3E58512E0B}' Node2:'{DDE3457B-DB9A-4DA9-9564-6F49E0F296BD}' Name:'transformer1' SwitchState1:1 SwitchState2:1 TransformerType:'10750/420 V  630 kVA' Earthing1:0 Earthing2:1 TapPosition:3 
#VoltageControl OwnControl:True ControlStatus:1 MeasureSide:2 SetPoint:0.4 DeadBand:0.1 Rc:0.008 CompoundingAtGeneration:True Pmin1:-100 Pmax1:100 
#TransformerType ShortName:'630 KVA' Snom:0.63 Unom1:10.75 Unom2:0.42 Uk:4 Pk:5.2 Po:0.745 R0:0.0019 Z0:0.011 Ik2s:21.6 WindingConnection1:'D' WindingConnection2:'YN' ClockNumber:5 TapSide:1 TapSize:0.25 TapMin:5 TapNom:3 TapMax:1 
#Dynamics KneeFluxLeg1:1.04 KneeFluxLeg2:1.04 KneeFluxLeg3:1.04 MagnetizingInductanceRatioLeg1:1000 MagnetizingInductanceRatioLeg2:1000 MagnetizingInductanceRatioLeg3:1000 RemanentFluxLeg1:0.7 RemanentFluxLeg2:0.7 RemanentFluxLeg3:0.7 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' Strings1X:12 Strings1Y:6 Strings2X:-15 Strings2Y:6 MidStringsY:24 FaultStringsX:-20 FaultStringsY:20 NoteY:5 FirstCorners:'{(14940 14780) }' SecondCorners:'{(15100 14780) }' 
[]

[SPECIAL TRANSFORMER]
#General GUID:'{B46288EF-B591-45B1-8BAF-818BF23CB626}' CreationTime:44875.5992225231 MutationDate:45463 RevisionDate:44877 Node1:'{1ED177A7-1F5D-4D81-8DE7-AB3E58512E0B}' Node2:'{A79AFDE9-4096-4BEB-AB63-2B851D7FC6D1}' Name:'special_trans1' SwitchState1:1 SwitchState2:1 SpecialTransformerType:'10600/10600 V/23 MVA Smit' Earthing:0 TapPosition:5 TapPosition_b:0 TapPosition_c:0 
#VoltageControl Present:True Status:True MeasureSide:2 Setpoint:10 Deadband:0.1 Rc:0.008 CompoundingAtGeneration:True Pmin1:-100 Pmax1:100 
#PControl Pmin:0 Pmax:0 
#SpecialTransformerType Sort:11 ShortName:'23 MVA' Snom:23 Unom1:10.6 Unom2:10.6 Ukmin:0.45 Uknom:0.5 Ukmax:0.6 Z0:0.019 Ik2s:19 TapSide:1 TapSize:0.15 TapMin:1 TapNom:7 TapMax:13 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' Strings1X:12 Strings1Y:6 Strings2X:-15 Strings2Y:6 MidStringsX:24 FaultStringsX:-20 FaultStringsY:20 NoteX:5 FirstCorners:'{(14940 14840) (15000 14840) }' SecondCorners:'{(15100 15020) (15000 15020) }' 
[]

[REACTANCECOIL]
#General GUID:'{7EB807C6-F2ED-42D0-83C4-478CDCCE17F3}' CreationTime:44875.5954900694 Node1:'{7FF722ED-33B3-4761-84AC-A164310D3C86}' Node2:'{1ED177A7-1F5D-4D81-8DE7-AB3E58512E0B}' Name:'rcoil1' SwitchState1:1 SwitchState2:1 ReactanceCoilType:'0.3 ohm 300 A' 
#ReactanceCoilType ShortName:'0.3 Ohm' Unom:10 Inom:300 X:0.3 X0:0.3 X2:0.3 Ik2s:14.4 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' Strings1X:12 Strings1Y:6 Strings2X:-15 Strings2Y:6 MidStringsY:24 FaultStringsX:-20 FaultStringsY:20 NoteY:5 FirstCorners:'{(14800 14820) }' SecondCorners:'{(14940 14820) }' 
[]

[THREEWINDINGSTRANSFORMER]
#General GUID:'{CA65D7DA-A029-4D30-867C-91D85ACADF41}' CreationTime:44886.4468122917 MutationDate:45463 Node1:'{1ED177A7-1F5D-4D81-8DE7-AB3E58512E0B}' Node2:'{DDE3457B-DB9A-4DA9-9564-6F49E0F296BD}' Node3:'{7848DBC8-9685-452C-89AF-9AB308224689}' SwitchState1:1 SwitchState2:1 SwitchState3:1 Earthing1:0 Earthing2:1 Re2:2 Xe2:3 Earthing3:1 Re3:1 Xe3:5 TapControlled:1 TapFixed:2 
#VoltageControl Present:True Status:1 MeasuringSide:2 Setpoint:0.4 Deadband:0.1 Rc:0.008 
#ThreewindingsTransformerType Snom1:30 Snom2:40 Snom3:35 Unom1:11 Unom2:0.4 Unom3:0.4 Uk12:1 Uk13:2 Uk23:3 Pk12:10 Pk13:20 Pk23:30 SAt12:20 SAt13:30 SAt23:40 Po:60 Io:3 Connection1:'D' Connection2:'YN' Connection3:'YN' ClockNumber12:5 ClockNumber13:7 TapSideControlled:1 TapSizeControlled:0.1 TapminControlled:-5 TapnomControlled:1 TapmaxControlled:6 TapSideFixed:2 TapSizeFixed:0.01 TapminFixed:-7 TapnomFixed:2 TapmaxFixed:8 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15020 Y:14680 Strings1X:12 Strings1Y:6 Strings2X:-15 Strings2Y:6 Strings3X:-15 Strings3Y:6 MidStringsX:20 MidStringsY:20 NoteX:-20 NoteY:20 FirstCorners:'{(14940 14740) (15020 14740) }' SecondCorners:'{(15100 14740) (15020 14740) }' ThirdCorners:'{(15040 14620) (14940 14620) (14940 14680) }' 
[]

[SOURCE]
#General Node:'{7FF722ED-33B3-4761-84AC-A164310D3C86}' GUID:'{65633711-995E-4B8E-B2BE-B554AA90E013}' CreationTime:44875.5933864468 Name:'source1' SwitchState:1 Uref:1 Sk2nom:1100 Sk2min:990 Sk2max:1100 R/X:0.1 Z0/Z1:3 Profile:'{A4D813DF-1EE1-4153-806C-DC228D251A79}' 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:14720 Y:14820 Strings1X:-15 Strings1Y:6 SymbolStringsX:-125 NoteX:5 NoteY:5 
[]

[SYNCHRONOUS GENERATOR]
#General Node:'{A79AFDE9-4096-4BEB-AB63-2B851D7FC6D1}' GUID:'{4B10F0F0-E728-4494-ABFF-613A2AA96524}' CreationTime:44875.605146088 Name:'syngen1' SwitchState:1 Pref:0.5 ControlSort:'C' Qref:0.16434205 CosRef:0.95 Uref:1 UQDroop:1 QlimitingType:1 Earthing:0 Profile:'{A4D813DF-1EE1-4153-806C-DC228D251A79}' 
#SynchronousGeneratorType Unom:11 Snom:1 CosNom:0.95 Qmax:0.1 rg:0.014 Xd2sat:0.2 UfMax:1.3 Xdsat:1.6 Nnom:3000 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15180 Y:15040 Strings1X:12 Strings1Y:6 SymbolStringsX:125 NoteX:-5 NoteY:5 
[]

[LOAD]
#General Node:'{DDE3457B-DB9A-4DA9-9564-6F49E0F296BD}' GUID:'{2E0B8D28-9881-482A-B2F6-A92D90D2FEEB}' CreationTime:44875.6091168403 Name:'load1' SwitchState:1 P:0.1 Q:0.1 Fp1:1 Fq1:1 Fp2:1 Fq2:1 Fp3:1 Fq3:1 LoadBehaviour:'{0993B8C8-033F-4345-AF80-FDB160F0427D}' LoadGrowth:'{EC874317-80BD-4714-AC1C-F611E2BDAF50}' Profile:'{A4D813DF-1EE1-4153-806C-DC228D251A79}' Earthing:0 HarmonicImpedance:True 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15220 Y:14680 Strings1X:12 Strings1Y:6 SymbolStringsX:165 NoteX:-5 NoteY:5 
[]

[TRANSFORMERLOAD]
#General Node:'{DDE3457B-DB9A-4DA9-9564-6F49E0F296BD}' GUID:'{A7821D13-99F5-42A5-8D0E-2BF4B0F1FD23}' CreationTime:44875.6029419907 MutationDate:45457 RevisionDate:45457 Name:'transformer_load_2' SwitchState:1 LoadP:0.2 LoadQ:0.02 LoadBehaviour:'{30ACBB5E-4C4B-42C5-B5A6-958BE8B77CFC}' LoadGrowth:'{086EADBF-BA43-4A2B-B048-A37DF08CD17D}' Profile:'{A4D813DF-1EE1-4153-806C-DC228D251A79}' GenerationGrowth:'{EC874317-80BD-4714-AC1C-F611E2BDAF50}' GenerationProfile:'{A4D813DF-1EE1-4153-806C-DC228D251A79}' PVGrowth:'{EC874317-80BD-4714-AC1C-F611E2BDAF50}' PVProfile:'{A4D813DF-1EE1-4153-806C-DC228D251A79}' TapPosition:2 
#TransformerType Snom:0.5 Unom1:0.4 Unom2:0.2 Uk:8 Pk:40 Po:50 WindingConnection1:'YN' WindingConnection2:'YN' ClockNumber:0 TapSide:1 TapSize:0.01 TapMin:1 TapNom:2 TapMax:4 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15180 Y:14900 Strings1X:12 Strings1Y:6 SymbolStringsX:205 NoteX:-5 NoteY:5 
#General Node:'{DDE3457B-DB9A-4DA9-9564-6F49E0F296BD}' GUID:'{68A2AEA4-2263-4902-81CD-E06C114D727C}' CreationTime:45457.4723790857 Name:'transformer_load_1' SwitchState:1 LoadP:0.2 LoadQ:0.02 LoadBehaviour:'{30ACBB5E-4C4B-42C5-B5A6-958BE8B77CFC}' LoadGrowth:'{086EADBF-BA43-4A2B-B048-A37DF08CD17D}' Profile:'{A4D813DF-1EE1-4153-806C-DC228D251A79}' GenerationP:0.03 GenerationQ:0.01 GenerationGrowth:'{EC874317-80BD-4714-AC1C-F611E2BDAF50}' GenerationProfile:'{A4D813DF-1EE1-4153-806C-DC228D251A79}' PVPnom:0.01 PVGrowth:'{EC874317-80BD-4714-AC1C-F611E2BDAF50}' PVProfile:'{A4D813DF-1EE1-4153-806C-DC228D251A79}' TapPosition:2 
#TransformerType Snom:0.5 Unom1:0.4 Unom2:0.2 Uk:8 Pk:40 Po:50 WindingConnection1:'YN' WindingConnection2:'YN' ClockNumber:0 TapSide:1 TapSize:0.01 TapMin:1 TapNom:2 TapMax:4 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15180 Y:14840 Strings1X:12 Strings1Y:6 SymbolStringsX:205 NoteX:-5 NoteY:5 
[]

[SHUNTCAPACITOR]
#General Node:'{A79AFDE9-4096-4BEB-AB63-2B851D7FC6D1}' GUID:'{346C4567-5D4D-439A-BC74-BA77684040F9}' CreationTime:44875.6093570833 Name:'shunt1' SwitchState:1 Q:0.5 Unom:11 Profile:'{A4D813DF-1EE1-4153-806C-DC228D251A79}' Earthing:0 
#ActiveFilter h3:100 h5:100 h7:100 h9:100 h11:100 h13:100 h15:100 h17:100 h19:100 h21:100 h23:100 h25:100 h27:100 h29:100 h31:100 h33:100 h35:100 h37:100 h39:100 h41:100 h43:100 h45:100 h47:100 h49:100 h51:100 h53:100 h55:100 h57:100 h59:100 h61:100 h63:100 h65:100 h67:100 h69:100 h71:100 h73:100 h75:100 h77:100 h79:100 h81:100 h83:100 h85:100 h87:100 h89:100 h91:100 h93:100 h95:100 h97:100 h99:100 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15200 Y:15100 Strings1X:12 Strings1Y:6 SymbolStringsX:125 NoteX:-5 NoteY:5 
[]

[SHUNTCOIL]
#General Node:'{A79AFDE9-4096-4BEB-AB63-2B851D7FC6D1}' GUID:'{394FBE07-A7FA-4249-B7FF-EC42A1C55303}' CreationTime:44886.4459253472 SwitchState:1 Q:0.5 Unom:11 Profile:'{A4D813DF-1EE1-4153-806C-DC228D251A79}' Earthing:0 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15180 Y:15160 Strings1X:12 Strings1Y:6 SymbolStringsX:125 NoteX:-5 NoteY:5 
[]

[EARTHINGTRANSFORMER]
#General Node:'{DDE3457B-DB9A-4DA9-9564-6F49E0F296BD}' GUID:'{1B60A9EB-9FB9-4C80-BDAC-717D8F24D428}' CreationTime:44875.6047998032 Name:'zztrans1' SwitchState:1 Earthing:1 EarthingTransformerType:'7 Ohm' 
#EarthingTransformerType X0:7 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15180 Y:14940 Strings1X:12 Strings1Y:6 SymbolStringsX:165 NoteX:-5 NoteY:5 
[]

[WINDTURBINE]
#General Node:'{DDE3457B-DB9A-4DA9-9564-6F49E0F296BD}' GUID:'{AC17891F-98ED-4539-AB95-3D22CDD27F4C}' CreationTime:44875.6020721991 MutationDate:44877 RevisionDate:44877 Name:'wind1' SwitchState:1 NumberOf:1 WindSpeedOrPref:0 WindSpeed:12 Profile:'{A4D813DF-1EE1-4153-806C-DC228D251A79}' AxisHeight:30 WindTurbineType:'Async/75 kVA/0.4 kV' 
#WindTurbineType Pnom:0.075 Unom:0.40000001 Ik/Inom:7 R/X:0.1 WindSpeedCutIn:4 WindSpeedNom:15 WindSpeedCuttingOut:26 WindSpeedCuttedOut:26 
#QControl CosRef:1 NoPNoQ:True Input1:0.95 Output1:0.5 Input2:1 Output2:0 Input3:1 Output3:0 Input4:1.03 Output4:-0.5 Input5:1.05 Output5:-0.5 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15240 Y:14800 Strings1X:12 Strings1Y:6 SymbolStringsX:185 NoteX:-5 NoteY:5 
[]

[PV]
#General Node:'{DDE3457B-DB9A-4DA9-9564-6F49E0F296BD}' GUID:'{186B67F9-F676-48CD-81A7-F5ECFDCB4EF2}' CreationTime:44875.6000511458 Name:'pv1' SwitchState:1 Scaling:1000 Profile:'{A4D813DF-1EE1-4153-806C-DC228D251A79}' Longitude:52 Latitude:5 Panel1Pnom:0.1 Panel1Orientation:180 Panel1Slope:30 Panel2Pnom:0.1 Panel2Orientation:180 Panel2Slope:30 Panel3Pnom:0.1 Panel3Orientation:180 Panel3Slope:30 
#Inverter Snom:0.5 Ik/Inom:1 EfficiencyType:'0,1 pu: 93 %; 1 pu: 97 %' 
#QControl CosRef:1 NoPNoQ:True Input1:0.95 Output1:0.5 Input2:1 Output2:0 Input3:1 Output3:0 Input4:1.03 Output4:-0.5 Input5:1.05 Output5:-0.5 
#EfficiencyType Input1:0.05 Output1:0 Input2:0.1 Output2:93 Input3:0.2 Output3:95 Input4:0.3 Output4:96 Input5:1 Output5:97 
#Presentation Sheet:'{AC5FD754-220B-47EF-B98C-367CB49E8C75}' X:15180 Y:14740 Strings1X:12 Strings1Y:6 SymbolStringsX:185 NoteX:-5 NoteY:5 
[]

)vnf";

std::string_view const json_result_string =
    R"({"version":"1.0","type":"input","is_batch":false,"attributes":{},"data":{"node":[{"id":0,"u_rated":11},{"id":1,"u_rated":11},{"id":2,"u_rated":0.4},{"id":3,"u_rated":11},{"id":4,"u_rated":0.4}]}})";
} // namespace

using enum PGM_IO_ExperimentalFeatures;

TEST_CASE("Test PGM_IO_create_vnf_converter") {
    PGM_IO_ExperimentalFeatures experimental_feature_flag = PGM_IO_experimental_features_disabled;

    SUBCASE("Test PGM_IO_create_vnf_converter without experimental feature flag") {
        PGM_IO_Handle* handle = PGM_IO_create_handle();
        auto* converter = PGM_IO_create_pgm_vnf_converter(handle, "", experimental_feature_flag);
        CHECK(PGM_IO_error_code(handle) == PGM_IO_regular_error);
        PGM_IO_destroy_pgm_vnf_converter(converter);
        PGM_IO_destroy_handle(handle);
    }

    SUBCASE("Test PGM_IO_create_vnf_converter with experimental feature flag") {
        PGM_IO_Handle* handle = PGM_IO_create_handle();
        experimental_feature_flag = PGM_IO_experimental_features_enabled;
        auto* converter = PGM_IO_create_pgm_vnf_converter(handle, basic_vision_9_7_vnf_file, experimental_feature_flag);
        CHECK(converter != nullptr);
        PGM_IO_destroy_pgm_vnf_converter(converter);
        PGM_IO_destroy_handle(handle);
    }
}

TEST_CASE("Test PGM_IO_get_vnf_input_data") {
    PGM_IO_Handle* handle = PGM_IO_create_handle();
    PGM_IO_ExperimentalFeatures const experimental_feature_flag = PGM_IO_experimental_features_enabled;

    auto* converter = PGM_IO_create_pgm_vnf_converter(handle, basic_vision_9_7_vnf_file, experimental_feature_flag);
    CHECK(converter != nullptr);

    auto const* const json_result = PGM_IO_pgm_vnf_converter_get_input_data(handle, converter);
    CHECK(json_result == json_result_string);

    PGM_IO_destroy_pgm_vnf_converter(converter);
    PGM_IO_destroy_handle(handle);
}

TEST_CASE("Test PGM_IO_get_example_vnf_input_data") {
    PGM_IO_Handle* handle = PGM_IO_create_handle();
    PGM_IO_ExperimentalFeatures const experimental_feature_flag = PGM_IO_experimental_features_enabled;

    auto* converter = PGM_IO_create_pgm_vnf_converter(handle, basic_vision_9_7_vnf_file, experimental_feature_flag);
    REQUIRE(PGM_IO_error_code(handle) == PGM_IO_no_error);
    REQUIRE(converter != nullptr);

    auto const* const json_result = PGM_IO_pgm_vnf_converter_get_input_data(handle, converter);
    REQUIRE(PGM_IO_error_code(handle) == PGM_IO_no_error);
    CHECK(json_result == json_result_string);

    PGM_IO_destroy_pgm_vnf_converter(converter);
    PGM_IO_destroy_handle(handle);
}

} // namespace power_grid_model_io_native
