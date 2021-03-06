#include <iostream>
#include <fstream>

#include "DGtal/io/readers/MeshReader.h"
#include "DGtal/io/writers/LongvolWriter.h"


#include "NormalAccumulator.h"

int
main(int argc,char **argv)
{

  DGtal::Mesh<DGtal::Z3i::RealPoint>  aMesh;
  aMesh << "../Samples/lemontree.off";
  NormalAccumulator acc(12);
  acc.initFromMesh(aMesh, true);

  acc.computeAccumulation();
  DGtal::LongvolWriter<NormalAccumulator::Image3D>::exportLongvol("testAccumulation.longvol",
                                                                  acc.getAccumulationImage());

  DGtal::trace.info() << acc;
  acc.computeConfidence();
  typedef DGtal::functors::Rescaling< double, DGtal::uint64_t> ScaleFctD;

  DGtal::trace.info() <<"max radius point:"<<  acc.getMaxRadiusPoint();
  DGtal::trace.info() <<"max accumulation point:"<<  acc.getMaxAccumulationPoint() ;
  DGtal::trace.info() <<"max accumulation point:"<<  acc.getDomain() ;

  ScaleFctD  confidencescale (0 , 1.0, 0, 1000);
  DGtal::LongvolWriter<NormalAccumulator::Image3DDouble,ScaleFctD>::exportLongvol("testConfidence.longvol",
                                                                                  acc.getConfidenceImage(),
                                                                                  true, confidencescale);

  acc.computeRadiusFromOrigins();
  double maxRadius = acc.getMaxRadius();
  ScaleFctD  radiiScale (0 , maxRadius, 0, maxRadius * 1000);
  DGtal::LongvolWriter<NormalAccumulator::Image3DDouble,ScaleFctD>::exportLongvol("testRadius.longvol",
                                                                                  acc.getRadiusImage(),
                                                                                  true, radiiScale);
  
  

  
}






