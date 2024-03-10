gaudi_add_module(GaudiGenerators
               SOURCES Pythia8/Pythia8_i.cpp
                       Pythia8/ReadTDS.cpp  
               LINK GaudiKernel
                    GaudiAlgLib
                    GaudiUtilsLib
                    Pythia8
                    ${GAUDI_ATOMIC_LIBS})