Interface Information
=====================

.. warning::
    This section is intended for **developers**, and may be irrelevant unless
    you intend to modify or expand the functionality of :ref:`Normal Use`.


GoldPackets
###########

:ref:`GoldPackets` is a custom designed packet standard, made by Team Gold for the EG-207 CMS.

The format is call/response based and detailed below:

+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
|          Inst           |   Byte   |       Reply        |   ACK    |   Fail    |                                                                        Note                                                                         |
+=========================+==========+====================+==========+===========+=====================================================================================================================================================+
| ``v``                   | ``0x76`` | ``v0.1_g70b...\n`` | ``ok\n`` | ``127\n`` | The "Version" Command will return the version as ascii. If it prints ``OK`` at the end it completed otherwise it may raise and print an error code. |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``w``                   | ``0x77`` | ``127\n``          | ``ok\n`` | ``127\n`` | Print the EEPROM warning, 0 if there is none.                                                                                                       |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``e``                   | ``0x65`` | ``127\n``          | ``ok\n`` | ``127\n`` | Print the EEPROM error, 0 if there is none.                                                                                                         |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``W``                   | ``0x45`` | ``127\n``          | ``ok\n`` | ``127\n`` | Clear the EEPROM warning. Will return the warning cleared.                                                                                          |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``E``                   | ``0x57`` | ``127\n``          | ``ok\n`` | ``127\n`` | Clear the EEPROM error. Will return the error cleared.                                                                                              |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``+``                   | ``0x2b`` | ``127\n``          | ``ok\n`` | ``127\n`` | DEBUG COMMAND, increments servo pos by 1 value and prints the new setpoint                                                                          |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``-``                   | ``0x2d`` | ``127\n``          | ``ok\n`` | ``127\n`` | DEBUG COMMAND, decrements servo pos by 1 value and prints the nw setpoint                                                                           |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``_``                   | ``0x5f`` | ``127\n``          | ``ok\n`` | ``127\n`` | DEBUG COMMAND, sets the servo pos to the ``MIN_DOOR_ANGLE`` and prints the angle                                                                    |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``=``                   | ``0x3d`` | ``127\n``          | ``ok\n`` | ``127\n`` | DEBUG COMMAND, sets the servo pos to the ``MAX_DOOR_ANGLE`` and prints the angle                                                                    |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``t``                   | ``0x74`` | ``32.00\n``        | ``ok\n`` | ``127\n`` | Lowercase t will poll the DHT11 for its temperature value and return it at that time.                                                               |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``h``                   | ``0x68`` | ``32.00\n``        | ``ok\n`` | ``127\n`` | Lowercase h will poll the DHT11 for its humidity value and return it at that time.                                                                  |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``r``                   | ``0x72`` | ``32.00\n``        | ``ok\n`` | ``127\n`` | Lowercase r will poll the rainflow sensor for its instant flow rate and print it out                                                                |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``l``                   | ``0x6c`` | ``32.00\n``        | ``ok\n`` | ``127\n`` | Lowercasee l will poll the CDS55 for the most recent average LUX reading.                                                                           |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``u``                   | ``0x75`` | ``32.00\n``        | ``ok\n`` | ``127\n`` | Lowercase U will poll the UV Sensor for the most recent average UV Index reading.                                                                   |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``<``                   | ``0x3c`` | ``\n``             | ``ok\n`` | ``127\n`` | DEBUG COMMAND, Create an artificial warning.                                                                                                        |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``>``                   | ``0x3e`` | ``\n``             | ``ok\n`` | ``127\n`` | DEBUG COMMAND, Create an artificial error.                                                                                                          |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``D``                   | ``0x44`` | ``0\n``            | ``ok\n`` | ``127\n`` | DEBUG COMMAND, Reset all tuning values to default.                                                                                                  |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+
| ``L<byte><byte><byte>`` | ``TBD``  | ``0\n``            | ``ok\n`` | ``127\n`` | DEBUG COMMAND, used to write new coefficients to the lux sensor.                                                                                    |
+-------------------------+----------+--------------------+----------+-----------+-----------------------------------------------------------------------------------------------------------------------------------------------------+

Communication Example
---------------------

.. code-block:: shell

    > v
    CDR-RELEASE-102-gaf0e-dirty
    ok
    > p
    ?70
    ok


Error Matrix
------------

Warnings:

+--------------+------------------------------------------------------------+
| Warning Code |                            Note                            |
+==============+============================================================+
| 10           | Sensor reading was out of scope or NaN                     |
+--------------+------------------------------------------------------------+
| 15           | Door was left ajar or rain sensor was left on              |
+--------------+------------------------------------------------------------+
| 69           | Self-inflicted warn, written by the LabView to the arduino |
+--------------+------------------------------------------------------------+

Errors:

+------------+-------------------------------------------------------------+
| Error Code |                            Note                             |
+============+=============================================================+
| 69         | Self-inflicted error, written by the LabView to the arduino |
+------------+-------------------------------------------------------------+
