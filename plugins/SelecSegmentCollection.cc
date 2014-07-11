#include "SelecSegmentCollection.h"


//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
SelecSegmentCollection::SelecSegmentCollection(const edm::ParameterSet& iConfig)
{
    L2seedsTag_ =  iConfig.getParameter<edm::InputTag>("L2seedsCollection");
    L2seedsIndex_ =  iConfig.getParameter<int>("L2seedsIndex");
    cscSegmentLabel_ = iConfig.getParameter<edm::InputTag>("cscSegmentCollection");
    dtSegmentLabel_ = iConfig.getParameter<edm::InputTag>("dtSegmentCollection");
  
    produces<CSCSegmentCollection>();
    produces<DTRecSegment4DCollection>();
}


SelecSegmentCollection::~SelecSegmentCollection()
{

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
SelecSegmentCollection::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    using namespace std;
    
    
    std::auto_ptr<CSCSegmentCollection> selectedCSC(new CSCSegmentCollection);
    std::auto_ptr<DTRecSegment4DCollection> selectedDT(new DTRecSegment4DCollection);


    // now read the L2 seeds collection :
    edm::Handle<TrajectorySeedCollection> L2seedsCollection;
    iEvent.getByLabel(L2seedsTag_,L2seedsCollection);
    
    Handle<CSCSegmentCollection> cscSegments;
    iEvent.getByLabel(cscSegmentLabel_, cscSegments);
    
    Handle<DTRecSegment4DCollection> dt4DSegments;
    iEvent.getByLabel(dtSegmentLabel_, dt4DSegments);
    
    
    const std::vector<TrajectorySeed>* L2seeds = 0;
    if (L2seedsCollection.isValid()) L2seeds = L2seedsCollection.product();
    else edm::LogVerbatim("L2seedsAnalyzer") << "L2 seeds collection not found !! ";
    
    
    int theLocalIndex = 0;
    for(TrajectorySeedCollection::const_iterator seed = L2seeds->begin(); seed != L2seeds->end(); ++seed){
        theLocalIndex++;
        if (!(theLocalIndex==L2seedsIndex_)) continue;
        cout << "nHits=" << seed->nHits() << endl;
        for(TrajectorySeed::recHitContainer::const_iterator itRecHits=seed->recHits().first; itRecHits!=seed->recHits().second; ++itRecHits) {
            const TrackingRecHit *seghit = &(*itRecHits);
            cout << (*seghit).isValid() << endl;
            float seedSegX = (*seghit).localPosition().x();
            float seedSegY = (*seghit).localPosition().y();
            float seedSegZ = (*seghit).localPosition().z();
            DetId segSeed = (*seghit).geographicalId();
            unsigned int segSeedRAW = segSeed.rawId();
            std::vector<CSCSegment> segv;
            std::vector<DTRecSegment4D> segvDT;
            for (CSCSegmentCollection::const_iterator seg=cscSegments->begin() ;
                 seg!=cscSegments->end() ; ++seg ){
                DetId geoidCSC = (*seg).geographicalId();
                const CSCSegment *theseg = &(*seg);
                unsigned int detidCSC = geoidCSC.rawId();
                if (detidCSC==segSeedRAW) {
                    float cscSegX = (*seg).localPosition().x();
                    float cscSegY = (*seg).localPosition().y();
                    float cscSegZ = (*seg).localPosition().z();
                    float dist = sqrt((seedSegX-cscSegX)*(seedSegX-cscSegX)+(seedSegY-cscSegY)*(seedSegY-cscSegY)+(seedSegZ-cscSegZ)*(seedSegZ-cscSegZ));
                    if (dist<0.00001) segv.push_back(*theseg);
                }
            }
           // cout << "nb of CSC= " << segv.size() << endl;
            //delete segv;
            if (segv.size()>0) selectedCSC->put(segSeedRAW, segv.begin(), segv.end());
           // cout << "try size CSCs=" << selectedCSC->size() << endl;
            for (DTRecSegment4DCollection::const_iterator seg=dt4DSegments->begin() ;
                 seg!=dt4DSegments->end() ; ++seg ){
                DetId geoidDT = (*seg).geographicalId();
                const DTRecSegment4D *theseg = &(*seg);
                unsigned int detidDT = geoidDT.rawId();
                if (detidDT==segSeedRAW) {
                    float dtSegX = (*seg).localPosition().x();
                    float dtSegY = (*seg).localPosition().y();
                    float dtSegZ = (*seg).localPosition().z();
                    float dist = sqrt((seedSegX-dtSegX)*(seedSegX-dtSegX)+(seedSegY-dtSegY)*(seedSegY-dtSegY)+(seedSegZ-dtSegZ)*(seedSegZ-dtSegZ));
                    if (dist<0.00001) {
                      segvDT.push_back(*theseg);
                        cout << "you pu on a un DT !! " << endl;
                    }
                }
            }
            if (segvDT.size()>0) selectedDT->put(segSeedRAW, segvDT.begin(), segvDT.end());
        }
    }

    
    for (DTRecSegment4DCollection::const_iterator seg=dt4DSegments->begin() ;
         seg!=dt4DSegments->end() ; ++seg ){
        cout << *seg << endl;
        DetId geoidDT = (*seg).geographicalId();
        unsigned int detidDT = geoidDT.rawId();
        cout << "detidDT=" << detidDT << endl;
    }
        
    for (CSCSegmentCollection::const_iterator seg=selectedCSC->begin() ;
         seg!=selectedCSC->end() ; ++seg ){
        cout << *seg << endl;
        DetId geoidCSC = (*seg).geographicalId();
        unsigned int detidCSC = geoidCSC.rawId();
        cout << "detidCSC=" << detidCSC << endl;
    }
    iEvent.put(selectedDT);
    iEvent.put(selectedCSC);
}

// ------------ method called once each job just before starting event loop  ------------
void 
SelecSegmentCollection::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SelecSegmentCollection::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
SelecSegmentCollection::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
SelecSegmentCollection::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
SelecSegmentCollection::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
SelecSegmentCollection::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SelecSegmentCollection::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SelecSegmentCollection);
