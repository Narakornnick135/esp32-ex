import 'package:flutter/material.dart';
import 'package:mqtt_client/mqtt_client.dart' as mqtt;
import 'package:mqtt_client/mqtt_server_client.dart';
import 'package:uuid/uuid.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      home: const MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});
  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  int _counter = 0;
  late MqttServerClient client;
  final Uuid uuid = Uuid();
  String _connectionStatus = 'Disconnected';

  @override
  void initState() {
    super.initState();
    _setupMqttClient();
  }

  Future<void> _setupMqttClient() async {
    final clientId =
        'flutter_${Uuid().v4().substring(0, 5)}'; // ตัวอย่าง: flutter_12345

    print("ID is >>>>>");
    print(clientId);

    final mqtt.MqttConnectMessage connMessage = mqtt.MqttConnectMessage()
        .authenticateAs('admin', 'admin')
        .withClientIdentifier(clientId)
        .startClean()
        .withWillQos(mqtt.MqttQos.atLeastOnce);
    client = MqttServerClient.withPort('smartgrid.cmru.ac.th', '', 1883);
    client.connectionMessage = connMessage;
    client.logging(on: false);
    client.useWebSocket = false;
    client.secure = false;
    client.setProtocolV31();
    client.keepAlivePeriod = 60;

    try {
      print('Attempting MQTT connection...');
      await client.connect();
      setState(() {
        _connectionStatus = 'Connected';
      });
      print('MQTT connected!');
    } catch (e) {
      print('MQTT connection failed: $e');
      setState(() {
        _connectionStatus = 'Connection Failed';
      });
    }
  }

// PING response received
  void pong() {
    print('Ping response client callback invoked');
  }

  void _incrementCounter() {
    setState(() {
      _counter++;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Text(
              'MQTT Connection Status: $_connectionStatus',
              style: TextStyle(
                  color: _connectionStatus == 'Connected'
                      ? Colors.green
                      : Colors.red),
            ),
            const Text(
              'You have pushed the button this many times:',
            ),
            Text(
              '$_counter',
              style: Theme.of(context).textTheme.headlineMedium,
            ),
          ],
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: _incrementCounter,
        tooltip: 'Increment',
        child: const Icon(Icons.add),
      ),
    );
  }

  @override
  void dispose() {
    client.disconnect();
    super.dispose();
  }
}
