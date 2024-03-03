import 'package:flutter/material.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: MyHomePage(),
    );
  }
}

class MyHomePage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Positioning Example'),
      ),
      body: Stack(
        children: [
          Positioned(
            left: 20,
            top: 20,
            child: ElevatedButton(
              onPressed: () {
                // Button action
              },
              child: Text('Top Left'),
            ),
          ),
          Positioned(
            right: 20,
            bottom: 20,
            child: ElevatedButton(
              onPressed: () {
                // Button action
              },
              child: Text('Bottom Right'),
            ),
          ),
        ],
      ),
    );
  }
}
