# Using Machine Learning algorithms in the search of a Z' boson vector at LHC
### Codes and source files

This repository has all the necessary files to replicate the multivariate analysis:

**makeTree Folder:**

  *makeTree.cc* creates TTree object for each of the source files (SG and BG)

**Exporting codes:**

  *exportFullSampleToCSV.cc* functions export data from .root to .csv format
```
  root exportFullSampleToCSV.cc
```
  *exportRandomSampleToCSV.cc* functions export data from .root to .csv format
```
  run: root exportRandomSampleToCSV.cc
```

**Histograms:**

  radomSampleHistograms.cc functions create the histograms for the random subsamples
```
  root radomSampleHistograms.cc
```

**ML analysis:**

  _____GeV_Analysis.ipynb shows the MVA analysis for each of the Z' mass samples

**Make samples:**

  *makeFullSample.cc* applies, to a initial raw simulations (not included here), the initial C_0 cuts to reduce QCD Background
```
  run: makeFullSample.cc
```  
  *makeRandomSample.cc* makes a random sub sample from fullSample with equal signal and background events
```
  run: makeRandomSample.cc
```
