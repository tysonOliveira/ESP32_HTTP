const express = require('express');

const app = express();

app.use(express.json());

let teste;

app.get('/dados', (req, res) => {
  res.status(200).send(teste);
})

app.post('/', (req, res) => {
  teste = { "Temperatura": req.body.temperatura, "Umidade": req.body.umidade };
  res.status(200).send(req.body);
  console.log("Temperatura:", req.body.temperatura, "umidade:", req.body.umidade);
})

app.listen('3000', () => { console.log('Server is running') });
