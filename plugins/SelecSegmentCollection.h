// -*- C++ -*-
//
// Package:    SelecSegmentCollection
// Class:      SelecSegmentCollection
// 
/**\class SelecSegmentCollection SelecSegmentCollection.cc hugues/SelecSegmentCollection/plugins/SelecSegmentCollection.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Hugues Louis Brun
//         Created:  Sun, 02 Mar 2014 16:15:47 GMT
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "DataFormats/TrackReco/interface/Track.h"

#include "DataFormats/DTRecHit/interface/DTRecHitCollection.h"
#include "DataFormats/DTRecHit/interface/DTRangeMapAccessor.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment2DCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"

#include "DataFormats/MuonDetId/interface/CSCDetId.h"
#include "DataFormats/CSCDigi/interface/CSCWireDigi.h"
#include "DataFormats/CSCDigi/interface/CSCWireDigiCollection.h"
#include "DataFormats/CSCDigi/interface/CSCStripDigi.h"
#include "DataFormats/CSCDigi/interface/CSCStripDigiCollection.h"
#include <DataFormats/CSCRecHit/interface/CSCRecHit2D.h>
#include "DataFormats/CSCRecHit/interface/CSCRecHit2DCollection.h"
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>

//
// class declaration
//

class SelecSegmentCollection : public edm::EDProducer {
   public:
      explicit SelecSegmentCollection(const edm::ParameterSet&);
      ~SelecSegmentCollection();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      
      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
    
    edm::InputTag L2seedsTag_;
    edm::InputTag cscSegmentLabel_;
    edm::InputTag dtSegmentLabel_;
    int L2seedsIndex_;
};

