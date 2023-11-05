import dataStore from 'nedb-promise';

export class NoteStore {
  constructor({ filename, autoload }) {
    this.store = dataStore({ filename, autoload });
  }
  
  async find(props) {
    return this.store.find(props);
  }
  
  async findOne(props) {
    return this.store.findOne(props);
  }
  
  async insert(note) {
    let noteText = note.text;
    let _id = note._id;
    let denumire = note.denumire;
    let substantaActiva = note.substantaActiva;
    let gramaj = note.gramaj;
    let dataExpirarii = note.dataExpirarii;
    if (!denumire && ! substantaActiva && !gramaj && !dataExpirarii) { // validation
      throw new Error('Missing properties')
    }

    // let _id = note.id;
    // let description = note.description;
    // let price = note.price;
    // let priceEstimation = note.priceEstimation;
    // let ownerUsername = note.ownerUsername;
    // if (!description && ! price && !priceEstimation && !ownerUsername) { // validation
    //   throw new Error('Missing properties')
    // }
    return this.store.insert(note);
  };
  
  async update(props, note) {
    return this.store.update(props, note);
  }
  
  async remove(props) {
    return this.store.remove(props);
  }
}

export default new NoteStore({ filename: './db/notes.json', autoload: true });