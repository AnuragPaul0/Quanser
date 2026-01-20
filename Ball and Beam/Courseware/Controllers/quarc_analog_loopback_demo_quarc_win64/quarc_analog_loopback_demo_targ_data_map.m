    function targMap = targDataMap(),

    ;%***********************
    ;% Create Parameter Map *
    ;%***********************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 5;
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
        ;% Auto data (quarc_analog_loopback_demo_P)
        ;%
            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% quarc_analog_loopback_demo_P.HILReadAnalog_channels
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% quarc_analog_loopback_demo_P.HILWriteAnalog_channels
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 2;

            nTotData = nTotData + section.nData;
            paramMap.sections(1) = section;
            clear section

            section.nData     = 19;
            section.data(19)  = dumData; %prealloc

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_OOTerminate
                    section.data(1).logicalSrcIdx = 2;
                    section.data(1).dtTransOffset = 0;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_OOExit
                    section.data(2).logicalSrcIdx = 3;
                    section.data(2).dtTransOffset = 1;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_OOStart
                    section.data(3).logicalSrcIdx = 4;
                    section.data(3).dtTransOffset = 2;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_OOEnter
                    section.data(4).logicalSrcIdx = 5;
                    section.data(4).dtTransOffset = 3;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AOFinal
                    section.data(5).logicalSrcIdx = 6;
                    section.data(5).dtTransOffset = 4;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_POFinal
                    section.data(6).logicalSrcIdx = 7;
                    section.data(6).dtTransOffset = 5;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AIHigh
                    section.data(7).logicalSrcIdx = 8;
                    section.data(7).dtTransOffset = 6;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AILow
                    section.data(8).logicalSrcIdx = 9;
                    section.data(8).dtTransOffset = 7;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AOHigh
                    section.data(9).logicalSrcIdx = 10;
                    section.data(9).dtTransOffset = 8;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AOLow
                    section.data(10).logicalSrcIdx = 11;
                    section.data(10).dtTransOffset = 9;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AOInitial
                    section.data(11).logicalSrcIdx = 12;
                    section.data(11).dtTransOffset = 10;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AOWatchdog
                    section.data(12).logicalSrcIdx = 13;
                    section.data(12).dtTransOffset = 11;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_POFrequency
                    section.data(13).logicalSrcIdx = 14;
                    section.data(13).dtTransOffset = 12;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_POInitial
                    section.data(14).logicalSrcIdx = 15;
                    section.data(14).dtTransOffset = 13;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_POWatchdog
                    section.data(15).logicalSrcIdx = 16;
                    section.data(15).dtTransOffset = 14;

                    ;% quarc_analog_loopback_demo_P.SignalGenerator_Amplitude
                    section.data(16).logicalSrcIdx = 17;
                    section.data(16).dtTransOffset = 15;

                    ;% quarc_analog_loopback_demo_P.SignalGenerator_Frequency
                    section.data(17).logicalSrcIdx = 18;
                    section.data(17).dtTransOffset = 16;

                    ;% quarc_analog_loopback_demo_P.SignalGenerator1_Amplitude
                    section.data(18).logicalSrcIdx = 19;
                    section.data(18).dtTransOffset = 17;

                    ;% quarc_analog_loopback_demo_P.SignalGenerator1_Frequency
                    section.data(19).logicalSrcIdx = 20;
                    section.data(19).dtTransOffset = 18;

            nTotData = nTotData + section.nData;
            paramMap.sections(2) = section;
            clear section

            section.nData     = 4;
            section.data(4)  = dumData; %prealloc

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_CKChannels
                    section.data(1).logicalSrcIdx = 21;
                    section.data(1).dtTransOffset = 0;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_DOWatchdog
                    section.data(2).logicalSrcIdx = 22;
                    section.data(2).dtTransOffset = 1;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_EIInitial
                    section.data(3).logicalSrcIdx = 23;
                    section.data(3).dtTransOffset = 2;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_POModes
                    section.data(4).logicalSrcIdx = 24;
                    section.data(4).dtTransOffset = 3;

            nTotData = nTotData + section.nData;
            paramMap.sections(3) = section;
            clear section

            section.nData     = 4;
            section.data(4)  = dumData; %prealloc

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AIChannels
                    section.data(1).logicalSrcIdx = 25;
                    section.data(1).dtTransOffset = 0;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AOChannels
                    section.data(2).logicalSrcIdx = 26;
                    section.data(2).dtTransOffset = 2;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_EIChannels
                    section.data(3).logicalSrcIdx = 27;
                    section.data(3).dtTransOffset = 4;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_EIQuadrature
                    section.data(4).logicalSrcIdx = 28;
                    section.data(4).dtTransOffset = 6;

            nTotData = nTotData + section.nData;
            paramMap.sections(4) = section;
            clear section

            section.nData     = 37;
            section.data(37)  = dumData; %prealloc

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_Active
                    section.data(1).logicalSrcIdx = 29;
                    section.data(1).dtTransOffset = 0;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AOTerminate
                    section.data(2).logicalSrcIdx = 30;
                    section.data(2).dtTransOffset = 1;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AOExit
                    section.data(3).logicalSrcIdx = 31;
                    section.data(3).dtTransOffset = 2;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_DOTerminate
                    section.data(4).logicalSrcIdx = 32;
                    section.data(4).dtTransOffset = 3;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_DOExit
                    section.data(5).logicalSrcIdx = 33;
                    section.data(5).dtTransOffset = 4;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_POTerminate
                    section.data(6).logicalSrcIdx = 34;
                    section.data(6).dtTransOffset = 5;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_POExit
                    section.data(7).logicalSrcIdx = 35;
                    section.data(7).dtTransOffset = 6;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_CKPStart
                    section.data(8).logicalSrcIdx = 36;
                    section.data(8).dtTransOffset = 7;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_CKPEnter
                    section.data(9).logicalSrcIdx = 37;
                    section.data(9).dtTransOffset = 8;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_CKStart
                    section.data(10).logicalSrcIdx = 38;
                    section.data(10).dtTransOffset = 9;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_CKEnter
                    section.data(11).logicalSrcIdx = 39;
                    section.data(11).dtTransOffset = 10;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AIPStart
                    section.data(12).logicalSrcIdx = 40;
                    section.data(12).dtTransOffset = 11;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AIPEnter
                    section.data(13).logicalSrcIdx = 41;
                    section.data(13).dtTransOffset = 12;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AOPStart
                    section.data(14).logicalSrcIdx = 42;
                    section.data(14).dtTransOffset = 13;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AOPEnter
                    section.data(15).logicalSrcIdx = 43;
                    section.data(15).dtTransOffset = 14;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AOStart
                    section.data(16).logicalSrcIdx = 44;
                    section.data(16).dtTransOffset = 15;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AOEnter
                    section.data(17).logicalSrcIdx = 45;
                    section.data(17).dtTransOffset = 16;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_AOReset
                    section.data(18).logicalSrcIdx = 46;
                    section.data(18).dtTransOffset = 17;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_DOPStart
                    section.data(19).logicalSrcIdx = 47;
                    section.data(19).dtTransOffset = 18;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_DOPEnter
                    section.data(20).logicalSrcIdx = 48;
                    section.data(20).dtTransOffset = 19;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_DOStart
                    section.data(21).logicalSrcIdx = 49;
                    section.data(21).dtTransOffset = 20;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_DOEnter
                    section.data(22).logicalSrcIdx = 50;
                    section.data(22).dtTransOffset = 21;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_DOReset
                    section.data(23).logicalSrcIdx = 51;
                    section.data(23).dtTransOffset = 22;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_EIPStart
                    section.data(24).logicalSrcIdx = 52;
                    section.data(24).dtTransOffset = 23;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_EIPEnter
                    section.data(25).logicalSrcIdx = 53;
                    section.data(25).dtTransOffset = 24;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_EIStart
                    section.data(26).logicalSrcIdx = 54;
                    section.data(26).dtTransOffset = 25;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_EIEnter
                    section.data(27).logicalSrcIdx = 55;
                    section.data(27).dtTransOffset = 26;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_POPStart
                    section.data(28).logicalSrcIdx = 56;
                    section.data(28).dtTransOffset = 27;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_POPEnter
                    section.data(29).logicalSrcIdx = 57;
                    section.data(29).dtTransOffset = 28;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_POStart
                    section.data(30).logicalSrcIdx = 58;
                    section.data(30).dtTransOffset = 29;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_POEnter
                    section.data(31).logicalSrcIdx = 59;
                    section.data(31).dtTransOffset = 30;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_POReset
                    section.data(32).logicalSrcIdx = 60;
                    section.data(32).dtTransOffset = 31;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_OOReset
                    section.data(33).logicalSrcIdx = 61;
                    section.data(33).dtTransOffset = 32;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_DOFinal
                    section.data(34).logicalSrcIdx = 62;
                    section.data(34).dtTransOffset = 33;

                    ;% quarc_analog_loopback_demo_P.HILInitialize1_DOInitial
                    section.data(35).logicalSrcIdx = 63;
                    section.data(35).dtTransOffset = 34;

                    ;% quarc_analog_loopback_demo_P.HILReadAnalog_Active
                    section.data(36).logicalSrcIdx = 64;
                    section.data(36).dtTransOffset = 35;

                    ;% quarc_analog_loopback_demo_P.HILWriteAnalog_Active
                    section.data(37).logicalSrcIdx = 65;
                    section.data(37).dtTransOffset = 36;

            nTotData = nTotData + section.nData;
            paramMap.sections(5) = section;
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
        nTotSects     = 1;
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
        ;% Auto data (quarc_analog_loopback_demo_B)
        ;%
            section.nData     = 4;
            section.data(4)  = dumData; %prealloc

                    ;% quarc_analog_loopback_demo_B.HILReadAnalog_o1
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% quarc_analog_loopback_demo_B.HILReadAnalog_o2
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% quarc_analog_loopback_demo_B.SignalGenerator
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% quarc_analog_loopback_demo_B.SignalGenerator1
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

            nTotData = nTotData + section.nData;
            sigMap.sections(1) = section;
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
        nTotSects     = 4;
        sectIdxOffset = 1;

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
        ;% Auto data (quarc_analog_loopback_demo_DW)
        ;%
            section.nData     = 8;
            section.data(8)  = dumData; %prealloc

                    ;% quarc_analog_loopback_demo_DW.HILInitialize1_AIMinimums
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% quarc_analog_loopback_demo_DW.HILInitialize1_AIMaximums
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 2;

                    ;% quarc_analog_loopback_demo_DW.HILInitialize1_AOMinimums
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 4;

                    ;% quarc_analog_loopback_demo_DW.HILInitialize1_AOMaximums
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 6;

                    ;% quarc_analog_loopback_demo_DW.HILInitialize1_AOVoltages
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 8;

                    ;% quarc_analog_loopback_demo_DW.HILInitialize1_FilterFrequency
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 10;

                    ;% quarc_analog_loopback_demo_DW.HILReadAnalog_Buffer
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 12;

                    ;% quarc_analog_loopback_demo_DW.HILWriteAnalog_Buffer
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 14;

            nTotData = nTotData + section.nData;
            dworkMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% quarc_analog_loopback_demo_DW.HILInitialize1_Card
                    section.data(1).logicalSrcIdx = 8;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(2) = section;
            clear section

            section.nData     = 4;
            section.data(4)  = dumData; %prealloc

                    ;% quarc_analog_loopback_demo_DW.HILReadAnalog_PWORK
                    section.data(1).logicalSrcIdx = 9;
                    section.data(1).dtTransOffset = 0;

                    ;% quarc_analog_loopback_demo_DW.Scope_PWORK.LoggedData
                    section.data(2).logicalSrcIdx = 10;
                    section.data(2).dtTransOffset = 1;

                    ;% quarc_analog_loopback_demo_DW.Scope1_PWORK.LoggedData
                    section.data(3).logicalSrcIdx = 11;
                    section.data(3).dtTransOffset = 2;

                    ;% quarc_analog_loopback_demo_DW.HILWriteAnalog_PWORK
                    section.data(4).logicalSrcIdx = 12;
                    section.data(4).dtTransOffset = 3;

            nTotData = nTotData + section.nData;
            dworkMap.sections(3) = section;
            clear section

            section.nData     = 3;
            section.data(3)  = dumData; %prealloc

                    ;% quarc_analog_loopback_demo_DW.HILInitialize1_ClockModes
                    section.data(1).logicalSrcIdx = 13;
                    section.data(1).dtTransOffset = 0;

                    ;% quarc_analog_loopback_demo_DW.HILInitialize1_QuadratureModes
                    section.data(2).logicalSrcIdx = 14;
                    section.data(2).dtTransOffset = 1;

                    ;% quarc_analog_loopback_demo_DW.HILInitialize1_InitialEICounts
                    section.data(3).logicalSrcIdx = 15;
                    section.data(3).dtTransOffset = 3;

            nTotData = nTotData + section.nData;
            dworkMap.sections(4) = section;
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


    targMap.checksum0 = 1326062989;
    targMap.checksum1 = 1111253509;
    targMap.checksum2 = 935659910;
    targMap.checksum3 = 1260770040;

