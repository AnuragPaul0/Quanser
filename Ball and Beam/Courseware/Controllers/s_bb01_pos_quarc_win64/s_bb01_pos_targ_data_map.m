    function targMap = targDataMap(),

    ;%***********************
    ;% Create Parameter Map *
    ;%***********************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 2;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc paramMap
        ;%
        paramMap.nSections           = nTotSects;
        paramMap.sectIdxOffset       = sectIdxOffset;
            paramMap.sections(nTotSects) = dumSection; %prealloc
        paramMap.nTotData            = -1;

        ;%
        ;% Auto data (s_bb01_pos_P)
        ;%
            section.nData     = 31;
            section.data(31)  = dumData; %prealloc

                    ;% s_bb01_pos_P.K_AMP
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% s_bb01_pos_P.K_bb
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% s_bb01_pos_P.Kc
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% s_bb01_pos_P.THETA_MAX
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

                    ;% s_bb01_pos_P.THETA_MIN
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 4;

                    ;% s_bb01_pos_P.VMAX_AMP
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 5;

                    ;% s_bb01_pos_P.VMAX_DAC
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 6;

                    ;% s_bb01_pos_P.kp
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 7;

                    ;% s_bb01_pos_P.kv
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 8;

                    ;% s_bb01_pos_P.z
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 9;

                    ;% s_bb01_pos_P.SRV02SignalGenerator_a
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 10;

                    ;% s_bb01_pos_P.SRV02SignalGenerator_f
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 11;

                    ;% s_bb01_pos_P.Amplitudecm_gain
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 12;

                    ;% s_bb01_pos_P.Constantcm_gain
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 13;

                    ;% s_bb01_pos_P.SetPointWeight_gain
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 14;

                    ;% s_bb01_pos_P.SRV02SignalGenerator_sig_type
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 15;

                    ;% s_bb01_pos_P.Constant_Value
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 16;

                    ;% s_bb01_pos_P.Setpointm_Gain
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 17;

                    ;% s_bb01_pos_P.VeltoPos_IC
                    section.data(19).logicalSrcIdx = 18;
                    section.data(19).dtTransOffset = 18;

                    ;% s_bb01_pos_P.HighPassFilterrads_A
                    section.data(20).logicalSrcIdx = 19;
                    section.data(20).dtTransOffset = 19;

                    ;% s_bb01_pos_P.HighPassFilterrads_C
                    section.data(21).logicalSrcIdx = 20;
                    section.data(21).dtTransOffset = 20;

                    ;% s_bb01_pos_P.HighPassFilterrads_D
                    section.data(22).logicalSrcIdx = 21;
                    section.data(22).dtTransOffset = 21;

                    ;% s_bb01_pos_P.VeltoPos_IC_h
                    section.data(23).logicalSrcIdx = 22;
                    section.data(23).dtTransOffset = 22;

                    ;% s_bb01_pos_P.Highpassfilter_A
                    section.data(24).logicalSrcIdx = 23;
                    section.data(24).dtTransOffset = 23;

                    ;% s_bb01_pos_P.Highpassfilter_C
                    section.data(25).logicalSrcIdx = 24;
                    section.data(25).dtTransOffset = 25;

                    ;% s_bb01_pos_P.Gain_Gain
                    section.data(26).logicalSrcIdx = 25;
                    section.data(26).dtTransOffset = 27;

                    ;% s_bb01_pos_P.cmm_Gain
                    section.data(27).logicalSrcIdx = 26;
                    section.data(27).dtTransOffset = 28;

                    ;% s_bb01_pos_P.theta_ldeg_Gain
                    section.data(28).logicalSrcIdx = 27;
                    section.data(28).dtTransOffset = 29;

                    ;% s_bb01_pos_P.AcctoVel_IC
                    section.data(29).logicalSrcIdx = 28;
                    section.data(29).dtTransOffset = 30;

                    ;% s_bb01_pos_P.TransferFcn_A
                    section.data(30).logicalSrcIdx = 29;
                    section.data(30).dtTransOffset = 31;

                    ;% s_bb01_pos_P.TransferFcn_C
                    section.data(31).logicalSrcIdx = 30;
                    section.data(31).dtTransOffset = 32;

            nTotData = nTotData + section.nData;
            paramMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% s_bb01_pos_P.ManualSwitch_CurrentSetting
                    section.data(1).logicalSrcIdx = 31;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            paramMap.sections(2) = section;
            clear section


            ;%
            ;% Non-auto Data (parameter)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        paramMap.nTotData = nTotData;



    ;%**************************
    ;% Create Block Output Map *
    ;%**************************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 2;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc sigMap
        ;%
        sigMap.nSections           = nTotSects;
        sigMap.sectIdxOffset       = sectIdxOffset;
            sigMap.sections(nTotSects) = dumSection; %prealloc
        sigMap.nTotData            = -1;

        ;%
        ;% Auto data (s_bb01_pos_B)
        ;%
            section.nData     = 43;
            section.data(43)  = dumData; %prealloc

                    ;% s_bb01_pos_B.SquareWave
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% s_bb01_pos_B.Clock
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% s_bb01_pos_B.SineWave
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% s_bb01_pos_B.MultiportSwitch
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

                    ;% s_bb01_pos_B.SliderGain
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 4;

                    ;% s_bb01_pos_B.SliderGain_h
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 5;

                    ;% s_bb01_pos_B.Setpointcm
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 6;

                    ;% s_bb01_pos_B.Setpointm
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 7;

                    ;% s_bb01_pos_B.VeltoPos
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 8;

                    ;% s_bb01_pos_B.PositionErrorm
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 9;

                    ;% s_bb01_pos_B.ZeroLocationrads
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 10;

                    ;% s_bb01_pos_B.SliderGain_j
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 11;

                    ;% s_bb01_pos_B.WeighedPositionErrorms
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 12;

                    ;% s_bb01_pos_B.Derivativems
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 13;

                    ;% s_bb01_pos_B.HighPassFilterrads
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 14;

                    ;% s_bb01_pos_B.ManualSwitch
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 15;

                    ;% s_bb01_pos_B.ControlOutputms
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 16;

                    ;% s_bb01_pos_B.ProportionalGainradsm
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 17;

                    ;% s_bb01_pos_B.DesiredAngleSaturationrad
                    section.data(19).logicalSrcIdx = 18;
                    section.data(19).dtTransOffset = 18;

                    ;% s_bb01_pos_B.VeltoPos_i
                    section.data(20).logicalSrcIdx = 19;
                    section.data(20).dtTransOffset = 19;

                    ;% s_bb01_pos_B.PositionErrorrad
                    section.data(21).logicalSrcIdx = 20;
                    section.data(21).dtTransOffset = 20;

                    ;% s_bb01_pos_B.ProportionalGainVrad
                    section.data(22).logicalSrcIdx = 21;
                    section.data(22).dtTransOffset = 21;

                    ;% s_bb01_pos_B.Highpassfilter
                    section.data(23).logicalSrcIdx = 22;
                    section.data(23).dtTransOffset = 22;

                    ;% s_bb01_pos_B.VelocityGainVsrad
                    section.data(24).logicalSrcIdx = 23;
                    section.data(24).dtTransOffset = 23;

                    ;% s_bb01_pos_B.ControlOutput
                    section.data(25).logicalSrcIdx = 24;
                    section.data(25).dtTransOffset = 24;

                    ;% s_bb01_pos_B.AmplifierSaturationV
                    section.data(26).logicalSrcIdx = 25;
                    section.data(26).dtTransOffset = 25;

                    ;% s_bb01_pos_B.InverseAmplifierGainVV
                    section.data(27).logicalSrcIdx = 26;
                    section.data(27).dtTransOffset = 26;

                    ;% s_bb01_pos_B.DAQSaturationV
                    section.data(28).logicalSrcIdx = 27;
                    section.data(28).dtTransOffset = 27;

                    ;% s_bb01_pos_B.AmplifierGainVV
                    section.data(29).logicalSrcIdx = 28;
                    section.data(29).dtTransOffset = 28;

                    ;% s_bb01_pos_B.Gain
                    section.data(30).logicalSrcIdx = 29;
                    section.data(30).dtTransOffset = 29;

                    ;% s_bb01_pos_B.cmm
                    section.data(31).logicalSrcIdx = 30;
                    section.data(31).dtTransOffset = 31;

                    ;% s_bb01_pos_B.theta_ldeg
                    section.data(32).logicalSrcIdx = 31;
                    section.data(32).dtTransOffset = 33;

                    ;% s_bb01_pos_B.AcctoVel
                    section.data(33).logicalSrcIdx = 32;
                    section.data(33).dtTransOffset = 34;

                    ;% s_bb01_pos_B.TrigonometricFunction
                    section.data(34).logicalSrcIdx = 33;
                    section.data(34).dtTransOffset = 35;

                    ;% s_bb01_pos_B.ModelGainms2rad
                    section.data(35).logicalSrcIdx = 34;
                    section.data(35).dtTransOffset = 36;

                    ;% s_bb01_pos_B.TransferFcn
                    section.data(36).logicalSrcIdx = 35;
                    section.data(36).dtTransOffset = 37;

                    ;% s_bb01_pos_B.t
                    section.data(37).logicalSrcIdx = 36;
                    section.data(37).dtTransOffset = 38;

                    ;% s_bb01_pos_B.MultiportSwitch_g
                    section.data(38).logicalSrcIdx = 37;
                    section.data(38).dtTransOffset = 39;

                    ;% s_bb01_pos_B.t12f
                    section.data(39).logicalSrcIdx = 38;
                    section.data(39).dtTransOffset = 40;

                    ;% s_bb01_pos_B.R0t12f
                    section.data(40).logicalSrcIdx = 39;
                    section.data(40).dtTransOffset = 41;

                    ;% s_bb01_pos_B.Sum1
                    section.data(41).logicalSrcIdx = 40;
                    section.data(41).dtTransOffset = 42;

                    ;% s_bb01_pos_B.R0
                    section.data(42).logicalSrcIdx = 41;
                    section.data(42).dtTransOffset = 43;

                    ;% s_bb01_pos_B.Sum
                    section.data(43).logicalSrcIdx = 42;
                    section.data(43).dtTransOffset = 44;

            nTotData = nTotData + section.nData;
            sigMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% s_bb01_pos_B.t12f_o
                    section.data(1).logicalSrcIdx = 43;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(2) = section;
            clear section


            ;%
            ;% Non-auto Data (signal)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        sigMap.nTotData = nTotData;



    ;%*******************
    ;% Create DWork Map *
    ;%*******************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 2;
        sectIdxOffset = 2;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc dworkMap
        ;%
        dworkMap.nSections           = nTotSects;
        dworkMap.sectIdxOffset       = sectIdxOffset;
            dworkMap.sections(nTotSects) = dumSection; %prealloc
        dworkMap.nTotData            = -1;

        ;%
        ;% Auto data (s_bb01_pos_DW)
        ;%
            section.nData     = 4;
            section.data(4)  = dumData; %prealloc

                    ;% s_bb01_pos_DW.TimeStampA
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% s_bb01_pos_DW.LastUAtTimeA
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% s_bb01_pos_DW.TimeStampB
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% s_bb01_pos_DW.LastUAtTimeB
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

            nTotData = nTotData + section.nData;
            dworkMap.sections(1) = section;
            clear section

            section.nData     = 3;
            section.data(3)  = dumData; %prealloc

                    ;% s_bb01_pos_DW.VmV_PWORK.LoggedData
                    section.data(1).logicalSrcIdx = 4;
                    section.data(1).dtTransOffset = 0;

                    ;% s_bb01_pos_DW.theta_ldeg_PWORK.LoggedData
                    section.data(2).logicalSrcIdx = 5;
                    section.data(2).dtTransOffset = 1;

                    ;% s_bb01_pos_DW.xcm_PWORK.LoggedData
                    section.data(3).logicalSrcIdx = 6;
                    section.data(3).dtTransOffset = 2;

            nTotData = nTotData + section.nData;
            dworkMap.sections(2) = section;
            clear section


            ;%
            ;% Non-auto Data (dwork)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        dworkMap.nTotData = nTotData;



    ;%
    ;% Add individual maps to base struct.
    ;%

    targMap.paramMap  = paramMap;
    targMap.signalMap = sigMap;
    targMap.dworkMap  = dworkMap;

    ;%
    ;% Add checksums to base struct.
    ;%


    targMap.checksum0 = 253096066;
    targMap.checksum1 = 3786206437;
    targMap.checksum2 = 1581647296;
    targMap.checksum3 = 3111862015;

