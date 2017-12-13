# Using Machine Learning algorithms in the search of a Z' boson vector at LHC
## Codes and source files
---

This repository has all the necessary files to replicate the multivariate
analysis. Source codes are divided in:

makeTree:
  makeTree.cc creates TTree object for each of the source files (SG and BG)

Exporting codes:
---
  exportFullSampleToCSV.cc functions export data from .root to .csv format
  run: root exportFullSampleToCSV.cc
---
  exportRandomSampleToCSV.cc functions export data from .root to .csv format
  run: root exportRandomSampleToCSV.cc
---

Histograms:
---
  radomSampleHistograms.cc functions create the exploratory histograms for the
  ransom subsamples
  run: root radomSampleHistograms.cc
---

ML analysis:
  ____GeV_Analysis.ipynb shows the MVA analysis for each of the Z' masses samples

Make samples:

  makeFullSample.cc applies, to a initial raw simulations (not included here), the initial C_0 cuts to reduce QCD Background
```
  run: makeFullSample.cc
```  
  makeRandomSample.cc makes a random sub sample from fullSample equally balanced
  through signal and background
```
  run: makeRandomSample.cc
``
