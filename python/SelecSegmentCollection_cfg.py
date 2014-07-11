import FWCore.ParameterSet.Config as cms

process = cms.Process("ALZ")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/tmp/hbrun/theRECOfile.root'
    )
)

process.selecSegmentCollection1 = cms.EDProducer('SelecSegmentCollection',
                                                L2seedsCollection = cms.InputTag("ancientMuonSeed"),
                                                L2seedsIndex = cms.int32(1),
                                                cscSegmentCollection = cms.InputTag("cscSegments"),
                                                dtSegmentCollection = cms.InputTag("dt4DSegments")
)


process.selecSegmentCollection2 = process.selecSegmentCollection1.clone()
process.selecSegmentCollection2.L2seedsIndex = cms.int32(2);

process.selecSegmentCollection3 = process.selecSegmentCollection1.clone()
process.selecSegmentCollection3.L2seedsIndex = cms.int32(3);

process.selecSegmentCollection4 = process.selecSegmentCollection1.clone()
process.selecSegmentCollection4.L2seedsIndex = cms.int32(4);

process.selecSegmentCollection5 = process.selecSegmentCollection1.clone()
process.selecSegmentCollection5.L2seedsIndex = cms.int32(5);







process.out = cms.OutputModule("PoolOutputModule",
                               outputCommands = cms.untracked.vstring(
                                                                      'drop *',
                                                                      'keep *_standAloneMuons_*_RECO',
                                                                      'keep *_muons_*_RECO',
                                                                      'keep *_dt4DSegments_*_RECO',
                                                                      'keep *_cscSegments_*_RECO',
                                                                      'keep *_*_*_ALZ'),
                               fileName = cms.untracked.string('testRECOouput.root')
                               )
  
process.p = cms.Path(process.selecSegmentCollection1*process.selecSegmentCollection2*process.selecSegmentCollection3*process.selecSegmentCollection4*process.selecSegmentCollection5)

print "the sequence"
print process.p 

process.outpath = cms.EndPath(process.out)
