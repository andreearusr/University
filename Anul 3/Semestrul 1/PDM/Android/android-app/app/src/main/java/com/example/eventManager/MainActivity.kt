package com.example.eventManager

import android.content.Context
import android.hardware.Sensor
import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import androidx.navigation.findNavController
import androidx.navigation.ui.AppBarConfiguration
import androidx.navigation.ui.navigateUp
import androidx.navigation.ui.setupActionBarWithNavController
import android.view.Menu
import android.view.MenuItem
import android.view.View
import androidx.constraintlayout.widget.ConstraintLayout
import com.example.eventManager.core.ConnectionLiveData
import com.example.eventManager.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var appBarConfiguration: AppBarConfiguration
    private lateinit var binding: ActivityMainBinding

    private val TAG = "MainActivity"
//    private lateinit var sensorManager: SensorManager
//    private var light: Sensor? = null

    private lateinit var cld : ConnectionLiveData

    private lateinit var layout1 : ConstraintLayout
    private lateinit var layout2 : ConstraintLayout

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        setSupportActionBar(binding.toolbar)

        val navController = findNavController(R.id.nav_host_fragment_content_main)
        appBarConfiguration = AppBarConfiguration(navController.graph)
        setupActionBarWithNavController(navController, appBarConfiguration)

        checkNetworkConnection()

        layout1 = findViewById(R.id.layout1)
        layout2 = findViewById(R.id.layout2)

//        sensorManager = getSystemService(Context.SENSOR_SERVICE) as SensorManager
//        light = sensorManager.getDefaultSensor(Sensor.TYPE_LIGHT)
    }

    private fun checkNetworkConnection() {
        cld = ConnectionLiveData(application)

        cld.observe(this, { isConnected ->
            if (isConnected){
                layout1.visibility = View.VISIBLE
                layout2.visibility = View.GONE

            }else{
                layout1.visibility = View.GONE
                layout2.visibility = View.VISIBLE
            }

        })
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        // Inflate the menu; this adds items to the action bar if it is present.
        menuInflater.inflate(R.menu.menu_main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        return when (item.itemId) {
            R.id.action_settings -> true
            else -> super.onOptionsItemSelected(item)
        }
    }

    override fun onSupportNavigateUp(): Boolean {
        val navController = findNavController(R.id.nav_host_fragment_content_main)
        return navController.navigateUp(appBarConfiguration)
                || super.onSupportNavigateUp()
    }

//    override fun onAccuracyChanged(sensor: Sensor, accuracy: Int) {
//        Log.d(TAG, "onAccuracyChanged $accuracy");
//    }
//
//    override fun onSensorChanged(event: SensorEvent) {
//        // The light sensor returns a single value.
//        // Many sensors return 3 values, one for each axis.
//
//        val lux = event.values[0]
//        // Do something with this sensor value.
//        if (lux % 3 == 0f) {
//            Log.d(TAG, "onSensorChanged $lux");
//        }
//    }
//
//    override fun onResume() {
//        super.onResume()
//        light?.also {
//            sensorManager.registerListener(this, it, SensorManager.SENSOR_DELAY_NORMAL)
//        }
//    }
//
//    override fun onPause() {
//        super.onPause()
//        sensorManager.unregisterListener(this)
//    }
}