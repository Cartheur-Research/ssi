///////////////////////////////////////////////////////////////////////////////////////
///////// > openSMILE configuration file, Geneva feature set <       //////////////////
/////////                                                            //////////////////
///////// (c) 2014 by audEERING                                      //////////////////
/////////     All rights reserved. See file COPYING for details.     //////////////////
///////////////////////////////////////////////////////////////////////////////////////

;; for LEq
[componentInstances:cComponentManager]
instance[egemapsv01a_energyRMS].type=cEnergy

[egemapsv01a_energyRMS:cEnergy]
reader.dmLevel = gemapsv01a_frame25
writer.dmLevel = egemapsv01a_energyRMS
;;\{\cm[bufferModeConf]}
htkcompatible = 0
rms = 0
energy2 = 1
log = 0


;;;;;;;;;;;;;;; spectral
[componentInstances:cComponentManager]
instance[egemapsv01a_logSpectral_flux].type=cSpectral

[egemapsv01a_logSpectral_flux:cSpectral]
reader.dmLevel=gemapsv01a_fftmagH25
writer.dmLevel=egemapsv01a_logSpectral_flux
;;\{\cm[bufferModeRbLagConf]}
flux = 1
centroid = 0
maxPos=0
minPos=0
entropy = 0
flatness = 0
harmonicity = 0
sharpness = 0
variance=0
skewness=0
kurtosis=0
alphaRatio = 0
hammarbergIndex = 0
slope = 0
normBandEnergies = 1
squareInput = 1
useLogSpectrum = 1
freqRange = 0-5000
oldSlopeScale = 0

;;;;;;;;;; cepstral ;;;;;;;;;;;;;;;;;;;
[componentInstances:cComponentManager]
instance[egemapsv01a_melspecMfcc].type=cMelspec
instance[egemapsv01a_mfcc].type=cMfcc

[egemapsv01a_melspecMfcc:cMelspec]
reader.dmLevel=gemapsv01a_fftmagH25
writer.dmLevel=egemapsv01a_melspecMfcc
copyInputName = 1
processArrayFields = 1
; htk compatible sample value scaling
htkcompatible = 1
nBands = 26
; use power spectrum instead of magnitude spectrum
usePower = 1
lofreq = 20
hifreq = 8000
specScale = mel
inverse = 0

[egemapsv01a_mfcc:cMfcc]
reader.dmLevel=egemapsv01a_melspecMfcc
writer.dmLevel=egemapsv01a_mfcc
;;\{\cm[bufferModeRbLagConf]}
copyInputName = 0
processArrayFields = 1
firstMfcc = 1
lastMfcc  = 4
cepLifter = 22.0
htkcompatible = 1


;;;;;;;;;;;; collecting, filtering, and renaming ;;;;;;;;;;;;;;;;,

/*
logSpectral     Hammarberg, AlphaRatio, spectralSlope  0-500, 500-1500
harmonics   H1-H2, H1-A3, HNRlog
logPitch    F0finalLog
jitterShimmer   jitterLocal, shimmerLocal
loudness
formants   F1-3 freq, F1 bandw (check!)
harmonics  F1-3 level relative
*/

[componentInstances:cComponentManager]
instance[egemapsv01a_lldSetSelectorE].type=cDataSelector
instance[egemapsv01a_lldSetSelectorNoF0LoudnZ].type=cDataSelector
instance[egemapsv01a_lldSetSelectorNoF0LoudnNz].type = cDataSelector
instance[egemapsv01a_logSpectralVoiced].type = cValbasedSelector
instance[egemapsv01a_logSpectralUnvoiced].type = cValbasedSelector
instance[egemapsv01a_lldSetSelectorSpectralNz].type=cDataSelector
instance[egemapsv01a_lldSetSelectorSpectralZ].type=cDataSelector

[egemapsv01a_lldSetSelectorE:cDataSelector]
reader.dmLevel = gemapsv01a_loudness;gemapsv01a_logSpectral;egemapsv01a_logSpectral_flux;egemapsv01a_mfcc
writer.dmLevel = egemapsv01a_lldsetE
;;\{\cm[bufferModeRbConf]}
selected = loudness;pcm_fftMag_alphaRatioDB;pcm_fftMag_hammarbergIndexDB;pcm_fftMag_logSpectralSlopeOfBand0-500;pcm_fftMag_logSpectralSlopeOfBand500-1500;pcm_fftMag_spectralFlux;mfcc[1];mfcc[2];mfcc[3];mfcc[4]
newNames = Loudness;alphaRatio;hammarbergIndex;slope0-500;slope500-1500;spectralFlux;mfcc1;mfcc2;mfcc3;mfcc4

[gemapsv01a_lldSetSelectorNoF0LoudnNz:cDataSelector]
reader.dmLevel = gemapsv01a_jitterShimmer;gemapsv01a_harmonics;gemapsv01a_formantsNz
writer.dmLevel = gemapsv01a_lldSetNoF0AndLoudnessNz
;;\{\cm[bufferModeRbConf]}
selected = jitterLocal;shimmerLocalDB;HarmonicsToNoiseRatioACFLogdB;HarmonicDifferenceLogRelH1-H2;HarmonicDifferenceLogRelH1-A3;formantFreqLpc[1];formantBandwidthLpc[1];FormantAmplitudeByMaxHarmonicLogRelF0[1];formantFreqLpc[2];FormantAmplitudeByMaxHarmonicLogRelF0[2];formantFreqLpc[3];FormantAmplitudeByMaxHarmonicLogRelF0[3]
newNames = jitterLocal;shimmerLocaldB;HNRdBACF;logRelF0-H1-H2;logRelF0-H1-A3;F1frequency;F1bandwidth;F1amplitudeLogRelF0;F2frequency;F2amplitudeLogRelF0;F3frequency;F3amplitudeLogRelF0


[egemapsv01a_lldSetSelectorNoF0LoudnZ:cDataSelector]
reader.dmLevel = gemapsv01a_logSpectral;egemapsv01a_logSpectral_flux;egemapsv01a_mfcc
writer.dmLevel = egemapsv01a_lldSetNoF0AndLoudnessZ
;;\{\cm[bufferModeRbConf]}
selected = pcm_fftMag_spectralFlux;mfcc[1];mfcc[2];mfcc[3];mfcc[4]
newNames = spectralFlux;mfcc1;mfcc2;mfcc3;mfcc4

[egemapsv01a_lldSetSelectorNoF0LoudnNz:cDataSelector]
reader.dmLevel = gemapsv01a_jitterShimmer;gemapsv01a_harmonics;gemapsv01a_formantsNz
writer.dmLevel = egemapsv01a_lldSetNoF0AndLoudnessNz
;;\{\cm[bufferModeRbConf]}
selected = jitterLocal;shimmerLocalDB;HarmonicsToNoiseRatioACFLogdB;HarmonicDifferenceLogRelH1-H2;HarmonicDifferenceLogRelH1-A3;formantFreqLpc[1];formantBandwidthLpc[1];FormantAmplitudeByMaxHarmonicLogRelF0[1];formantFreqLpc[2];formantBandwidthLpc[2];FormantAmplitudeByMaxHarmonicLogRelF0[2];formantFreqLpc[3];formantBandwidthLpc[3];FormantAmplitudeByMaxHarmonicLogRelF0[3]
newNames = jitterLocal;shimmerLocaldB;HNRdBACF;logRelF0-H1-H2;logRelF0-H1-A3;F1frequency;F1bandwidth;F1amplitudeLogRelF0;F2frequency;F2bandwidth;F2amplitudeLogRelF0;F3frequency;F3bandwidth;F3amplitudeLogRelF0

// select logspectral and mfcc for voiced sounds
[egemapsv01a_logSpectralVoiced:cValbasedSelector]
reader.dmLevel = gemapsv01a_lld_single_logF0;gemapsv01a_logSpectral;egemapsv01a_logSpectral_flux;egemapsv01a_mfcc
writer.dmLevel = egemapsv01a_logSpectralVoiced
;;\{\cm[bufferModeRbLagConf]}
idx=0
threshold=0.000001
removeIdx=1
zeroVec=1
outputVal=0.0

// select logspectral and mfcc for voiced sounds
[egemapsv01a_logSpectralUnvoiced:cValbasedSelector]
reader.dmLevel = gemapsv01a_lld_single_logF0;gemapsv01a_logSpectral;egemapsv01a_logSpectral_flux
writer.dmLevel = egemapsv01a_logSpectralUnvoiced
;;\{\cm[bufferModeRbLagConf]}
idx=0
invert = 1
threshold = 0.000001
removeIdx=1
zeroVec=1
outputVal=0.0

[egemapsv01a_lldSetSelectorSpectralNz:cDataSelector]
reader.dmLevel = egemapsv01a_logSpectralVoiced
writer.dmLevel = egemapsv01a_lldSetSpectralNz
;;\{\cm[bufferModeRbConf]}
selected = pcm_fftMag_alphaRatioDB;pcm_fftMag_hammarbergIndexDB;pcm_fftMag_logSpectralSlopeOfBand0-500;pcm_fftMag_logSpectralSlopeOfBand500-1500;pcm_fftMag_spectralFlux;mfcc[1];mfcc[2];mfcc[3];mfcc[4]
newNames = alphaRatioV;hammarbergIndexV;slopeV0-500;slopeV500-1500;spectralFluxV;mfcc1V;mfcc2V;mfcc3V;mfcc4V

[egemapsv01a_lldSetSelectorSpectralZ:cDataSelector]
reader.dmLevel = egemapsv01a_logSpectralUnvoiced
writer.dmLevel = egemapsv01a_lldSetSpectralZ
;;\{\cm[bufferModeRbConf]}
selected = pcm_fftMag_alphaRatioDB;pcm_fftMag_hammarbergIndexDB;pcm_fftMag_logSpectralSlopeOfBand0-500;pcm_fftMag_logSpectralSlopeOfBand500-1500;pcm_fftMag_spectralFlux
newNames = alphaRatioUV;hammarbergIndexUV;slopeUV0-500;slopeUV500-1500;spectralFluxUV


;;;;;;;;;;;;;;;;  smoothing ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
[componentInstances:cComponentManager]
instance[egemapsv01a_smoE].type=cContourSmoother
instance[egemapsv01a_smoNoFLZ].type=cContourSmoother
instance[egemapsv01a_smoNoF0andLoudnNz].type=cContourSmoother
instance[egemapsv01a_smoSpectralZ].type=cContourSmoother
instance[egemapsv01a_smoSpectralNz].type=cContourSmoother

[egemapsv01a_smoE:cContourSmoother]
reader.dmLevel = egemapsv01a_lldsetE
writer.dmLevel = egemapsv01a_lldsetE_smo
nameAppend = sma3
copyInputName = 1
noPostEOIprocessing = 0
smaWin = 3
noZeroSma = 0

[egemapsv01a_smoNoFLZ:cContourSmoother]
reader.dmLevel = egemapsv01a_lldSetNoF0AndLoudnessZ
writer.dmLevel = egemapsv01a_lldSetNoF0AndLoudnessZ_smo
;;\{\cm[bufferModeConf]}
nameAppend = sma3
copyInputName = 1
noPostEOIprocessing = 0
smaWin = 3
noZeroSma = 0

[egemapsv01a_smoNoF0andLoudnNz:cContourSmoother]
reader.dmLevel = egemapsv01a_lldSetNoF0AndLoudnessNz
writer.dmLevel = egemapsv01a_lldSetNoF0AndLoudnessNz_smo
;;\{\cm[bufferModeConf]}
nameAppend = sma3nz
copyInputName = 1
noPostEOIprocessing = 0
smaWin = 3
noZeroSma = 1

[egemapsv01a_smoSpectralZ:cContourSmoother]
reader.dmLevel = egemapsv01a_lldSetSpectralZ
writer.dmLevel = egemapsv01a_lldSetSpectralZ_smo
;;\{\cm[bufferModeConf]}
nameAppend = sma3nz
copyInputName = 1
noPostEOIprocessing = 0
smaWin = 3
; non-zero SMA is ok here, as it is inverted with 0's for the voiced parts
noZeroSma = 1

[egemapsv01a_smoSpectralNz:cContourSmoother]
reader.dmLevel = egemapsv01a_lldSetSpectralNz
writer.dmLevel = egemapsv01a_lldSetSpectralNz_smo
;;\{\cm[bufferModeConf]}
nameAppend = sma3nz
copyInputName = 1
noPostEOIprocessing = 0
smaWin = 3
noZeroSma = 1



