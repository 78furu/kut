cmake_minimum_required(VERSION 3.0.0)
project (Moons_orbit)

add_executable(MoonsOrbit integ.c)

target_link_libraries(MoonsOrbit m)

target_include_directories(
	MoonsOrbit
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(Gnuplot)


ADD_CUSTOM_TARGET(futtat)

ADD_CUSTOM_COMMAND(
	#WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Debug
	TARGET futtat
	COMMAND MoonsOrbit
	DEPENDS ../integ.c
	
)


ADD_CUSTOM_TARGET(plottol) 

ADD_CUSTOM_COMMAND(
	TARGET plottol
	COMMAND ${GNUPLOT} ../plotol.p
	OUTPUTS ${das}
	DEPENDS res.txt

	)

ADD_CUSTOM_TARGET(PDFKESZ)

ADD_CUSTOM_COMMAND(
	TARGET PDFKESZ
	COMMAND pdflatex ../ered.tex
	OUTPUTS ${das}

)
	
include(UseLATEX.cmake)

add_latex_document(../ered.tex
	INPUTS ../ered.tex	
	IMAGES build/ered.png
	FORCE_PDF
	TARGET_NAME fdds.pdf
	DEPENDS ered.png	
		)
ADD_CUSTOM_TARGET(MAKEPDF)

IF(LATEX_COMPILE)
  ADD_CUSTOM_COMMAND(
	TARGET MAKEPDF
    OUTPUT    ${Document_BINARY_DIR}/fdds.dvi
    DEPENDS   ../ered.tex
    COMMAND   ${LATEX_COMPILE}  
    ARGS      ../ered.tex 
    )
ENDIF(LATEX_COMPILE)

IF(DVIPDF_COMPILE)
  ADD_CUSTOM_COMMAND(
TARGET MAKEPDF
    OUTPUT    ${Document_BINARY_DIR}/megold.pdf
    DEPENDS   ${Document_BINARY_DIR}/fdds.dvi 
    COMMAND   ${DVIPDF_COMPILE}
    ARGS      ${Document_SOURCE_DIR}/fdds.dvi
    )
ENDIF(DVIPDF_COMPILE)



