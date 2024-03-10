gaudi_add_library(GaudiMyProjectLib
                  SOURCES src/Lib/FourMomentum.cpp
                  LINK PUBLIC GaudiKernel)

gaudi_add_module(GaudiMyProject
                SOURCES src/MomentumGenetator/MomentumGeneratorAlg.cpp
                        src/MomentumProcessor/MomentumProcessorAlg.cpp
                LINK GaudiKernel
                     GaudiAlgLib
                     GaudiUtilsLib
                     GaudiMyProjectLib
                     Pythia8
                     ${GAUDI_ATOMIC_LIBS})
 