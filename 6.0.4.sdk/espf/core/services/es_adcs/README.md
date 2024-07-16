# libADCS

# THIS IS NO LONGER VALID. DUE FOR AN UPDATE - 17.10.2022;


EnduroSat ADCS implementation library

Legacy Comments:
1. Known missing features /e.g. next iteration features/
   - Kalman filter (determination);
   - FL (Fuzzy Logic /Takagi-Sugeno/) optimal controller (control);
   - Optimal field for maneuver estimation (advanced for the bright future)
2. Known proposed features (for optimal determination and/or control) /e.g. next iteration features/
   - SGP4 propagator
   - Provision of several trigonometric "regimes" which use different representations of sine/cosine functions based on the angle's closeness to critical values (0, pi/2, pi, etc.)
3. Known limitations
   - Control operation not possible with consistent accuracy over the whole orbit (maneuvres depending on magnetic field geometry at given orbital position).
   - At any given orbital position (fixed magnetic field), only 2 degrees of freedom are available (no maneuvers are possible for an axis parallel to the local magnetic field) restricting any control accuracy. This is a physical constraint of MTQ-based systems.
4. Known bugs
   - B-Dot control oscillations tend to grow initially, although the growth is considerably small and the effect is dissipiated in the time evolution
5. Known issues
   - Detumbling, determination and control are separately tested modules with simulated results
   - Detumbling simulation tested completely with all aglorithms
   - Determination simulation considers only unit tests of the TRIAD algorithm, which are obtained by TRIAD propagator vectors (TRIAD propagator guaranteed as tested)
   - Determination not tested with the linear regression upgrade
   - Control simulation based on predefined determination inputs (fields, positions and angular velocity)