English below.
I denne mappa finnes:
	1. Javaserver med oppsett for Windows og instruks for bruk
	2. Kildekode for robot-applikasjon ligger i SDKroot/examples/
	3. Serverapplikasjon-hex til nRF51-dongle
	4. MATLAB-filer i Prosjektoppgave-Kybernetikk-2022 mappen
	5. Testfiler i Prosjektoppgave-Kybernetikk-2022 mappen
	6. Rapport til Prosjektoppgave ligger i Prosjektoppgave-Kybernetikk-2022 mappen

1. 	Se til at java og jdk er innstallert på pcen. Installer så Apache NetBeans. 
	Serverapplikasjonen heter SSNAR og kan åpnes fra Apache NetBeans. 
	Bibliotek må linkes til samsvarende filer. Alle filene finnes i mappa libraries. 
	Følg så instruksen som finnes på pdf videre.

2.	Kildekoden til robot-applikasjonen ligger i mappa robot-application og er laget som et prosjekt inni nRF5 SDK v15.0.0. 
	Gå til https://www.nordicsemi.com/Products/Development-software/nRF5-SDK/Download?lang=en#infotabs og last ned samme versjon av nRF5 SDK. 
	Last også ned SoftDevice. 
	For å kompilere (bygge) prosjektet trengs det en toolchain for ARM-prosessorer: GNU ARM Embedded 6.3 2017-q2-update, og CMake. 
	For å programmere (flashe til) roboten fra kommandolinjen trengs nRF Command Line tools. 
	Robot-applikasjonen er satt opp til å kunne plasseres i nRF5SDK-root/examples. 
	Hvis den plasseres med en annen dybde innad i SDKet, må Makefile redigeres (../ må legges til eller fra i SDK_ROOT)
	Prosjektet bygges med "make" og flashes med "make flash". "make flash" både bygger og flasher. 
	nRF52840-DK kobles til pcen med en USB-mikroUSB kabel tilkoblet i kortenden på DKet. 

3. 	En klar .hex-fil ligger i mappa. 
	Den flashes til nRF51-dongelen med applikasjonen Programmer som finnes inni nRF Connect for Desktop.
	nRF Connect for Desktop, kan lastes ned herfra: https://www.nordicsemi.com/Products/Development-tools/nRF-Connect-for-desktop/Download#infotabs 
	Programmeringsinstruksjoner for nRF51-dongelen kan finnes her: https://infocenter.nordicsemi.com/pdf/nRF51_Dongle_UG_v1.0.pdf
	Men i stedet for å bruke nRF GO Studio, bruker du Programmer, som nevnt. 

4.	MATLAB-filene inneholder ny implementasjon av api() funksjon. api() genereres til C code med MATLAB coder funksjonalitet.

5. 	Testfiler for plot, plotter funksjoner

6.	Rapport til Prosjektoppgave Magnus Isdal Kolbeinsen