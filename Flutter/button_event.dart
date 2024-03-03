import 'package:flutter/material.dart';

void main() => runApp(MyApp());

class MyApp extends StatefulWidget {
  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  String _labelText = 'Initial Text';

  void _updateLabel() {
    // อัพเดทข้อความของ label เมื่อฟังก์ชันนี้ถูกเรียก
    setState(() {
      _labelText = 'Updated Text';
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: Text('Flutter Label Update Example'),
        ),
        body: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              Text(
                _labelText,
                style: TextStyle(fontSize: 24),
              ),
              ElevatedButton(
                onPressed: _updateLabel,
                child: Text('Update Label'),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
